/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

/*
 * irqk.c
 *
 * ============================================================================
 * Copyright (c) Texas Instruments Inc 2006
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied or provided.
 * ============================================================================
 */
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/cdev.h>
#include <linux/mm.h>
#include <linux/interrupt.h>

#include <asm/io.h>
#include <asm/memory.h>
#include <asm/uaccess.h>

#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,26)
#include <asm/arch/cpu.h>
#include <asm/arch/hardware.h>
#include <asm/arch/irqs.h>
#else
// the following are guesses for the upcoming LSP 2.10 for Linux 2.6.28
#include <mach/hardware.h>
#include <mach/irqs.h>
#include <linux/clk.h>
#if defined(LSP_210)
#include <mach/cpu.h>
#else   /* defined(LSP_210) */
#include <mach/cputype.h>
#include <mach/mux.h>
#endif  /* defined(LSP_210) */
#endif

#include "irqk.h"

#if 0
#  if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36)
#  define USE_UNLOCKED_IOCTL
#  else
#  undef USE_UNLOCKED_IOCTL
#  endif
#else
/*
 * Just use it regardless of kernel version (since struct file_operations
 * has contained unlocked_ioctl for a long time now).
 */
#  define USE_UNLOCKED_IOCTL
#endif

/*
 * The following macros control version-dependent code:
 * USE_CACHE_VOID_ARG - #define if dmac functions take "void *" parameters,
 *    otherwise unsigned long is used
 * USE_CLASS_SIMPLE - #define if Linux version contains "class_simple*",
 *    otherwise "class*" or "device*" is used (see USE_CLASS_DEVICE usage).
 * USE_CLASS_DEVICE - #define if Linux version contains "class_device*",
 *    otherwise "device*" or "class_simple*" is used (see USE_CLASS_SIMPLE
 *    usage).
 * If neither USE_CLASS_SIMPLE nor USE_CLASS_DEVICE is set, there is further
 *    kernel version checking embedded in the module init & exit functions.
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,26)

#warning *** not a warning *** Note: LINUX_VERSION_CODE >= 2.6.26

#undef USE_CLASS_DEVICE
#undef USE_CLASS_SIMPLE

#elif LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,18)

#warning *** not a warning *** Note: 2.6.26 > LINUX_VERSION_CODE >= 2.6.18

#define USE_CLASS_DEVICE
#undef USE_CLASS_SIMPLE

#else  /* LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,18) */

#warning *** not a warning *** Note: LINUX_VERSION_CODE < 2.6.18

#define USE_CLASS_SIMPLE
#undef USE_CLASS_DEVICE

#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,18) */


/* A "channel" is an IRQ vector */
#define IRQK_NUMCHANNELS 64

#if defined(LSP_210)
/* holds physical address of ARM_INTMUX register */
unsigned int ARM_INTMUX;
#endif  /* defined(LSP_210) */

/* one channel per IRQ vector on ARM */
struct channel {
    struct list_head users;
    int transfer_complete;
    int resource;
    struct semaphore completion_sem;
    struct semaphore resource_sem;
};
static struct channel channels[IRQK_NUMCHANNELS];

typedef struct registered_user {
    struct list_head element;
    struct file *filp;
} registered_user;

#if defined(LSP_210)
struct intrinfo {
    int irq_num;
    int intrmux_bit;            // -1 if no bit in ARM_INTMUX register
    int intrmux_save;
    int intrmux_polarity;       // doesn't need to be set if intrmux_bit == -1
};
#else   /* defined(LSP_210) */
struct intrinfo {
    int irq_num;
    int irq_intmux_enable;
    int irq_intmux_disable;
};

static struct clk *mjcp_clk;
#endif  /* defined(LSP_210) */

static struct intrinfo intr_info[IRQK_NUMRESOURCES][IRQK_NUMLINES];

/* tracks resource usage */
static struct intrinfo *registered_resource[IRQK_NUMRESOURCES] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

#ifdef __DEBUG
#define __D(fmt, args...) printk(KERN_DEBUG "IRQK Debug: " fmt, ## args)
#else
#define __D(fmt, args...)
#endif

#define __E(fmt, args...) printk(KERN_ERR "IRQK Error: " fmt, ## args)

static int irq_major;
static atomic_t reference_count = ATOMIC_INIT(0);

#if (USE_UDEV==1)
#ifdef USE_CLASS_SIMPLE
static struct class_simple *irq_class;
#else
static struct class *irq_class;
#endif
#endif // USE_UDEV

static struct mutex irq_mutex;

/* Forward declaration of system calls */
#ifdef USE_UNLOCKED_IOCTL
static long ioctl(struct file *filp, unsigned int cmd, unsigned long args);
#else
static int ioctl(struct inode *inode, struct file *filp,
                 unsigned int cmd, unsigned long args);
#endif
static int open(struct inode *inode, struct file *filp);
static int release(struct inode *inode, struct file *filp);

static struct file_operations irq_fxns = {
    owner:   THIS_MODULE,
#ifdef USE_UNLOCKED_IOCTL
    unlocked_ioctl: ioctl,
#else
    ioctl:   ioctl,
#endif
    open:    open,
    release: release
};

#if defined(LSP_210)
static irqreturn_t irqHandler(int irq, void *dev_id, struct pt_regs *regs)
#else   /* defined(LSP_210) */
static irqreturn_t irqHandler(int irq, void *dev_id)
#endif  /* defined(LSP_210) */
{
    struct channel *channelp;

    __D("irqHandler: servicing irq #%d\n", irq);

    channelp = &channels[irq];
    if (channelp->resource != IRQK_NONE) {
        up(&channelp->completion_sem);
        channelp->transfer_complete = 1;
    }

    return IRQ_HANDLED;
}

/* releaseResource() must be called with irq_mutex held */
static void releaseResource(int resource)
{
    struct intrinfo *info;
    struct channel *channelp;
#if defined(LSP_210)
    int mask = -1;
    int bit = 0;
    int intrmux;
#endif  /* defined(LSP_210) */
    int irq;

    info = registered_resource[resource];
    irq = info->irq_num;

    free_irq(irq, NULL);

    channelp = &channels[irq];
    channelp->transfer_complete = 0;
    channelp->resource = IRQK_NONE;
    INIT_LIST_HEAD(&channelp->users);


#if defined(LSP_210)
    if (ARM_INTMUX) {
        if (info->intrmux_bit != -1) {
            __D("restoring ARM_INTMUX register ...\n");

            mask = 1 << info->intrmux_bit;
            bit = info->intrmux_save;
            intrmux = davinci_readl(ARM_INTMUX) & ~mask;
            intrmux |= bit;
            davinci_writel(intrmux, ARM_INTMUX);
        }
    }
#else   /* defined(LSP_210) */
    if (info->irq_intmux_disable != -1) {
            __D("restoring ARM_INTMUX register ...\n");
            davinci_cfg_reg(info->irq_intmux_disable);
    }
#endif  /* defined(LSP_210) */

    registered_resource[resource] = NULL;

    up(&channelp->resource_sem);
}

#ifdef USE_UNLOCKED_IOCTL
static long ioctl(struct file *filp, unsigned int cmd, unsigned long args)
#else
static int ioctl(struct inode *inode, struct file *filp,
                 unsigned int cmd, unsigned long args)
#endif
{
    unsigned int __user *argp = (unsigned int __user *) args;
    IRQK_Request req;
    int resource;
    int irq;
    int rv;
#if defined(LSP_210)
    int mask = -1;
    int bit = 0;
    int intrmux;
#endif  /* defined(LSP_210) */
    struct intrinfo *info;
    struct list_head *registeredlistp;
    struct list_head *unext;
    struct list_head *u;
    struct registered_user *user;
    struct channel *channelp;

    if (_IOC_TYPE(cmd) != _IOC_TYPE(IRQK_IOCMAGIC)) {
        __E("ioctl(): bad command type 0x%x (should be 0x%x)\n",
            _IOC_TYPE(cmd), _IOC_TYPE(IRQK_IOCMAGIC));
    }

    switch (cmd & IRQK_IOCCMDMASK) {
        case IRQK_IOCREQUESTIRQ:
            if (copy_from_user(&req, argp, sizeof(IRQK_Request))) {
                return -EFAULT;
            }
            info = &intr_info[req.resource][req.flags & IRQK_INTRLINEMASK];
            irq = info->irq_num;

            if (irq == -1) {
                __D("REQUESTIRQ: no support for requested IRQ %d\n", req.resource);

                return -EINVAL;
            }

            __D("REQUESTIRQ ioctl received for resource %d (irq #%d)\n",
                req.resource, irq);

            channelp = &channels[irq];

            if (channelp->resource != req.resource) {
                __D("REQUESTIRQ: waiting for resource semaphore...\n");

                if (down_interruptible(&channelp->resource_sem)) {
                    return -ERESTARTSYS;
                }

                __D("REQUESTIRQ: ... got it\n");
            }

            if (mutex_lock_interruptible(&irq_mutex)) {
                return -ERESTARTSYS;
            }

            if (channelp->resource == IRQK_NONE) {
                __D("REQUESTIRQ: not registered, requesting irq...\n");

                if ((rv = request_irq(irq, irqHandler, 0, "IRQK_Handler", NULL))) {
                    __D("REQUESTIRQ: couldn't install ISR, "
                        "request_irq returned %d\n", rv);

                    mutex_unlock(&irq_mutex);

                    up(&channelp->resource_sem);

                    return -EINVAL;
                }

                __D("REQUESTIRQ: ... got it\n");

                init_MUTEX_LOCKED(&channelp->completion_sem);
                channelp->transfer_complete = 0;
                channelp->resource = req.resource;

                registered_resource[req.resource] = info;

#if defined(LSP_210)
                if (ARM_INTMUX) {
                    if (info->intrmux_bit != -1) {
                        __D("writing ARM_INTMUX register ...\n");

                        mask = 1 << info->intrmux_bit;
                        bit = info->intrmux_polarity << info->intrmux_bit;
                        intrmux = davinci_readl(ARM_INTMUX);
                        info->intrmux_save = intrmux & mask;
                        intrmux &= ~mask;
                        intrmux |= bit;
                        davinci_writel(intrmux, ARM_INTMUX);
                    }
                }
#else   /* defined(LSP_210) */
                if (info->irq_intmux_enable != -1) {
                    __D("writing ARM_INTMUX register ...\n");
                    davinci_cfg_reg(info->irq_intmux_enable);
                }

#endif  /* defined(LSP_210) */
            }

            __D("REQUESTIRQ: adding filp %p to user list\n", filp);

            user = kmalloc(sizeof(struct registered_user), GFP_KERNEL);
            user->filp = filp;
            list_add(&user->element, &channelp->users);

            mutex_unlock(&irq_mutex);

            if (put_user(irq, argp)) {
                return -EFAULT;
            }

            break;

        case IRQK_IOCRELEASEIRQ:
            if (get_user(resource, argp)) {
                return -EFAULT;
            }

            info = registered_resource[resource];
            if (info == NULL) {
                __D("RELEASEIRQ: resource %d not registered\n", resource);

                return -EINVAL;
            }

            __D("RELEASEIRQ ioctl received for irq #%d\n", info->irq_num);

            if (mutex_lock_interruptible(&irq_mutex)) {
                return -ERESTARTSYS;
            }

            irq = info->irq_num;
            registeredlistp = &channels[irq].users;
            u = registeredlistp->next;

            while (u != registeredlistp) {
                unext = u->next;
                user = list_entry(u, struct registered_user, element);

                if (user->filp == filp) {
                    __D("RELEASEIRQ: Removing file %p from user list of IRQ #%d...\n",
                        filp, irq);

                    list_del(u);
                    kfree(user);

                    break;
                }

                u = unext;
            }

            if (u == registeredlistp) {
                __E("RELEASEIRQ: not a registered user of IRQ #%d\n", irq);

                mutex_unlock(&irq_mutex);

                return -EFAULT;
            }

            if (registeredlistp->next == registeredlistp) {
                __D("RELEASEIRQ: no more registered users, freeing busy IRQ #%d.\n", irq);

                releaseResource(resource);
            }

            mutex_unlock(&irq_mutex);

            break;

        case IRQK_IOCWAIT:
            if (get_user(resource, argp)) {
                return -EFAULT;
            }

            info = registered_resource[resource];
            if (info == NULL) {
                __D("WAIT: resource %d not registered\n", resource);

                return -EINVAL;
            }

            irq = info->irq_num;
            if (irq == -1) {
                __D("WAIT: resource %d not registered\n", resource);

                return -EINVAL;
            }

            __D("WAIT ioctl received for irq %d\n", irq);

            if (down_interruptible(&channels[irq].completion_sem)) {
                return -ERESTARTSYS;
            }

            channels[irq].transfer_complete = 0;

            __D("...got it\n");

            break;

        case IRQK_IOCDONE:
            if (get_user(resource, argp)) {
                return -EFAULT;
            }

            info = registered_resource[resource];
            if (info == NULL) {
                __D("DONE: resource %d not registered\n", resource);

                return -EINVAL;
            }

            irq = info->irq_num;
            if (irq == -1) {
                __D("DONE: resource %d not registered\n", resource);

                return -EINVAL;
            }

            __D("DONE ioctl received for irq #%d\n", irq);

            if (put_user(channels[irq].transfer_complete, argp)) {
                return -EFAULT;
            }

            break;

        default:
            __E("Unknown ioctl received: %d.\n", cmd);

            return -EINVAL;
    }

    return 0;
}

static int open(struct inode *inode, struct file *filp)
{
    __D("open: called.\n");

    atomic_inc(&reference_count);

    return 0;
}

static int release(struct inode *inode, struct file *filp)
{
    struct intrinfo *info;
    struct list_head *registeredlistp;
    struct list_head *unext;
    struct list_head *u;
    struct registered_user *user;
    int last_close = 0;
    int irq;
    int i;

    __D("close: called.\n");

    if (mutex_lock_interruptible(&irq_mutex)) {
        return -ERESTARTSYS;
    }

    if (atomic_dec_and_test(&reference_count)) {
        __D("close: all references closed, force freeing busy IRQs ...\n");

        last_close = 1;
    }

    /* unregister IRQs that are attached to the "current" process */
    for (i = 0; i < IRQK_NUMRESOURCES; i++) {
        if (registered_resource[i] != NULL) {
            info = registered_resource[i];
            irq = info->irq_num;
            registeredlistp = &channels[irq].users;
            u = registeredlistp->next;

            while (u != registeredlistp) {
                unext = u->next;
                user = list_entry(u, struct registered_user, element);

                if (last_close || user->filp == filp) {
                    __D("Removing file %p from user list of IRQ #%d...\n",
                        filp, irq);

                    list_del(u);
                    kfree(user);
                }

                u = unext;
            }

            if (registeredlistp->next == registeredlistp) {
                __D("close: no more registered users, force freeing busy IRQ #%d.\n", irq);
                releaseResource(i);
            }
        }
    }

    mutex_unlock(&irq_mutex);

    return 0;
}

static void banner(void)
{
    printk(KERN_INFO "IRQK module: built on " __DATE__ " at " __TIME__ "\n");
    printk(KERN_INFO "  Reference Linux version %d.%d.%d\n",
           (LINUX_VERSION_CODE & 0x00ff0000) >> 16,
           (LINUX_VERSION_CODE & 0x0000ff00) >> 8,
           (LINUX_VERSION_CODE & 0x000000ff) >> 0
          );
    printk(KERN_INFO "  File " __FILE__ "\n");
}

static int __init irqk_init(void)
{
    struct channel *channelp;
    int i;

    banner();

#if defined(LSP_210)
    ARM_INTMUX = 0;

    if (cpu_is_davinci_dm6467()) {
        __D("cpu is dm6467\n");
        __E("IRQK not supported for DM6467\n");

        return -EINVAL;
    }
#else   /* defined(LSP_210) */
    if (cpu_is_davinci_dm646x()) {
        __D("cpu is dm646x\n");
        __E("IRQK not supported for DM646x\n");

        return -EINVAL;
    }
#endif  /* defined(LSP_210) */
    else if (cpu_is_davinci_dm355()) {
        __D("cpu is dm355\n");

#if defined(LSP_210)
        ARM_INTMUX = DM365_ARM_INTMUX;  // no macro for 355, but same as 360

        intr_info[IRQK_NSF][IRQK_FLEXIBLELINE].irq_num = -1;
        intr_info[IRQK_NSF][IRQK_FLEXIBLELINE].intrmux_bit = -1;
        // 11
        intr_info[IRQK_IMX0][IRQK_FLEXIBLELINE].irq_num = IRQ_DM3XX_IMCOPINT;
        intr_info[IRQK_IMX0][IRQK_FLEXIBLELINE].intrmux_bit = -1;
        intr_info[IRQK_IMX1][IRQK_FLEXIBLELINE].irq_num = -1;
        intr_info[IRQK_IMX1][IRQK_FLEXIBLELINE].intrmux_bit = -1;
        intr_info[IRQK_MJCP][IRQK_FLEXIBLELINE].irq_num = -1;
        intr_info[IRQK_MJCP][IRQK_FLEXIBLELINE].intrmux_bit = -1;
        intr_info[IRQK_HDVICP0][IRQK_FLEXIBLELINE].irq_num = -1;
        intr_info[IRQK_HDVICP0][IRQK_FLEXIBLELINE].intrmux_bit = -1;
        intr_info[IRQK_HDVICP1][IRQK_FLEXIBLELINE].irq_num = -1;
        intr_info[IRQK_HDVICP1][IRQK_FLEXIBLELINE].intrmux_bit = -1;

        intr_info[IRQK_NSF][IRQK_FIXEDLINE].irq_num = -1;
        intr_info[IRQK_NSF][IRQK_FIXEDLINE].intrmux_bit = -1;
        // 10
        intr_info[IRQK_IMX0][IRQK_FIXEDLINE].irq_num = IRQ_IMXINT;
        intr_info[IRQK_IMX0][IRQK_FIXEDLINE].intrmux_bit = -1;
        intr_info[IRQK_IMX1][IRQK_FIXEDLINE].irq_num = -1;
        intr_info[IRQK_IMX1][IRQK_FIXEDLINE].intrmux_bit = -1;
        // 9
        intr_info[IRQK_MJCP][IRQK_FIXEDLINE].irq_num = IRQ_ASQINT;
        intr_info[IRQK_MJCP][IRQK_FIXEDLINE].intrmux_bit = -1;
        intr_info[IRQK_HDVICP0][IRQK_FIXEDLINE].irq_num = -1;
        intr_info[IRQK_HDVICP0][IRQK_FIXEDLINE].intrmux_bit = -1;
        intr_info[IRQK_HDVICP1][IRQK_FIXEDLINE].irq_num = -1;
        intr_info[IRQK_HDVICP1][IRQK_FIXEDLINE].intrmux_bit = -1;

#else   /* defined(LSP_210) */

        mjcp_clk = clk_get(NULL, "mjcp");
        if (IS_ERR(mjcp_clk)) {
            printk("Error getting mjcp clock\n");
            return -EINVAL;
        }
        clk_enable(mjcp_clk);

        intr_info[IRQK_NSF][IRQK_FLEXIBLELINE].irq_num = -1;
        intr_info[IRQK_NSF][IRQK_FLEXIBLELINE].irq_intmux_enable = -1;
        intr_info[IRQK_NSF][IRQK_FLEXIBLELINE].irq_intmux_disable = -1;
        // 11
        intr_info[IRQK_IMX0][IRQK_FLEXIBLELINE].irq_num = IRQ_DM355_IMCOPINT;
        intr_info[IRQK_IMX0][IRQK_FLEXIBLELINE].irq_intmux_enable = -1;
        intr_info[IRQK_IMX0][IRQK_FLEXIBLELINE].irq_intmux_disable = -1;
        intr_info[IRQK_IMX1][IRQK_FLEXIBLELINE].irq_num = -1;
        intr_info[IRQK_IMX1][IRQK_FLEXIBLELINE].irq_intmux_enable = -1;
        intr_info[IRQK_IMX1][IRQK_FLEXIBLELINE].irq_intmux_disable = -1;
        intr_info[IRQK_MJCP][IRQK_FLEXIBLELINE].irq_num = -1;
        intr_info[IRQK_MJCP][IRQK_FLEXIBLELINE].irq_intmux_enable = -1;
        intr_info[IRQK_MJCP][IRQK_FLEXIBLELINE].irq_intmux_disable = -1;
        intr_info[IRQK_HDVICP0][IRQK_FLEXIBLELINE].irq_num = -1;
        intr_info[IRQK_HDVICP0][IRQK_FLEXIBLELINE].irq_intmux_enable = -1;
        intr_info[IRQK_HDVICP0][IRQK_FLEXIBLELINE].irq_intmux_disable = -1;
        intr_info[IRQK_HDVICP1][IRQK_FLEXIBLELINE].irq_num = -1;
        intr_info[IRQK_HDVICP1][IRQK_FLEXIBLELINE].irq_intmux_enable = -1;
        intr_info[IRQK_HDVICP1][IRQK_FLEXIBLELINE].irq_intmux_disable = -1;

        intr_info[IRQK_NSF][IRQK_FIXEDLINE].irq_num = -1;
        intr_info[IRQK_NSF][IRQK_FIXEDLINE].irq_intmux_enable = -1;
        intr_info[IRQK_NSF][IRQK_FIXEDLINE].irq_intmux_disable = -1;
        // 10
        intr_info[IRQK_IMX0][IRQK_FIXEDLINE].irq_num = IRQ_IMXINT;
        intr_info[IRQK_IMX0][IRQK_FIXEDLINE].irq_intmux_enable = -1;
        intr_info[IRQK_IMX0][IRQK_FIXEDLINE].irq_intmux_disable = -1;
        intr_info[IRQK_IMX1][IRQK_FIXEDLINE].irq_num = -1;
        intr_info[IRQK_IMX1][IRQK_FIXEDLINE].irq_intmux_enable = -1;
        intr_info[IRQK_IMX1][IRQK_FIXEDLINE].irq_intmux_disable = -1;
        // 9
        intr_info[IRQK_MJCP][IRQK_FIXEDLINE].irq_num = IRQ_ASQINT;
        intr_info[IRQK_MJCP][IRQK_FIXEDLINE].irq_intmux_enable = -1;
        intr_info[IRQK_MJCP][IRQK_FIXEDLINE].irq_intmux_disable = -1;
        intr_info[IRQK_HDVICP0][IRQK_FIXEDLINE].irq_num = -1;
        intr_info[IRQK_HDVICP0][IRQK_FIXEDLINE].irq_intmux_enable = -1;
        intr_info[IRQK_HDVICP0][IRQK_FIXEDLINE].irq_intmux_disable = -1;
        intr_info[IRQK_HDVICP1][IRQK_FIXEDLINE].irq_num = -1;
        intr_info[IRQK_HDVICP1][IRQK_FIXEDLINE].irq_intmux_enable = -1;
        intr_info[IRQK_HDVICP1][IRQK_FIXEDLINE].irq_intmux_disable = -1;
#endif  /* defined(LSP_210) */
    }
    else if (cpu_is_davinci_dm365()) {
        __D("cpu is dm365\n");

#if defined(LSP_210)
        ARM_INTMUX = DM365_ARM_INTMUX;

        intr_info[IRQK_NSF][IRQK_FLEXIBLELINE].irq_num = IRQ_DM3XX_IMCOPINT;
        intr_info[IRQK_NSF][IRQK_FLEXIBLELINE].intrmux_bit = -1;

        intr_info[IRQK_IMX0][IRQK_FLEXIBLELINE].irq_num = IRQ_DM3XX_IMCOPINT;
        intr_info[IRQK_IMX0][IRQK_FLEXIBLELINE].intrmux_bit = -1;

        intr_info[IRQK_IMX1][IRQK_FLEXIBLELINE].irq_num = IRQ_DM3XX_IMCOPINT;
        intr_info[IRQK_IMX1][IRQK_FLEXIBLELINE].intrmux_bit = -1;

        // SEQ can't use "flex"
        intr_info[IRQK_MJCP][IRQK_FLEXIBLELINE].irq_num = -1;
        intr_info[IRQK_MJCP][IRQK_FLEXIBLELINE].intrmux_bit = -1;

        intr_info[IRQK_HDVICP0][IRQK_FLEXIBLELINE].irq_num = -1;
        intr_info[IRQK_HDVICP0][IRQK_FLEXIBLELINE].intrmux_bit = -1;

        intr_info[IRQK_HDVICP1][IRQK_FLEXIBLELINE].irq_num = -1;
        intr_info[IRQK_HDVICP1][IRQK_FLEXIBLELINE].intrmux_bit = -1;

        intr_info[IRQK_NSF][IRQK_FIXEDLINE].irq_num = IRQ_DM365_INSFINT;
        intr_info[IRQK_NSF][IRQK_FIXEDLINE].intrmux_bit = 25;
        intr_info[IRQK_NSF][IRQK_FIXEDLINE].intrmux_polarity = 1;

        intr_info[IRQK_IMX0][IRQK_FIXEDLINE].irq_num = IRQ_DM365_IMXINT0;
        intr_info[IRQK_IMX0][IRQK_FIXEDLINE].intrmux_bit = 0;
        intr_info[IRQK_IMX0][IRQK_FIXEDLINE].intrmux_polarity = 0;

        intr_info[IRQK_IMX1][IRQK_FIXEDLINE].irq_num = IRQ_DM365_IMXINT1;
        intr_info[IRQK_IMX1][IRQK_FIXEDLINE].intrmux_bit = 24;
        intr_info[IRQK_IMX1][IRQK_FIXEDLINE].intrmux_polarity = 1;

        intr_info[IRQK_MJCP][IRQK_FIXEDLINE].irq_num = IRQ_ASQINT;
        intr_info[IRQK_MJCP][IRQK_FIXEDLINE].intrmux_bit = -1;

        intr_info[IRQK_HDVICP0][IRQK_FIXEDLINE].irq_num = IRQ_DM365_KLD_ARMINT;
        intr_info[IRQK_HDVICP0][IRQK_FIXEDLINE].intrmux_bit = 0;
        intr_info[IRQK_HDVICP0][IRQK_FIXEDLINE].intrmux_polarity = 1;

        intr_info[IRQK_HDVICP1][IRQK_FIXEDLINE].irq_num = -1;
        intr_info[IRQK_HDVICP1][IRQK_FIXEDLINE].intrmux_bit = -1;

#else   /* defined(LSP_210) */

        mjcp_clk = clk_get(NULL, "mjcp");
        if (IS_ERR(mjcp_clk)) {
            printk("Error getting mjcp clock\n");
            return -EINVAL;
        }
        clk_enable(mjcp_clk);

        intr_info[IRQK_NSF][IRQK_FLEXIBLELINE].irq_num = IRQ_DM365_IMCOPINT;
        intr_info[IRQK_NSF][IRQK_FLEXIBLELINE].irq_intmux_enable = -1;
        intr_info[IRQK_NSF][IRQK_FLEXIBLELINE].irq_intmux_disable = -1;

        intr_info[IRQK_IMX0][IRQK_FLEXIBLELINE].irq_num = IRQ_DM365_IMCOPINT;
        intr_info[IRQK_IMX0][IRQK_FLEXIBLELINE].irq_intmux_enable = -1;
        intr_info[IRQK_IMX0][IRQK_FLEXIBLELINE].irq_intmux_disable = -1;

        intr_info[IRQK_IMX1][IRQK_FLEXIBLELINE].irq_num = IRQ_DM365_IMCOPINT;
        intr_info[IRQK_IMX1][IRQK_FLEXIBLELINE].irq_intmux_enable = -1;
        intr_info[IRQK_IMX1][IRQK_FLEXIBLELINE].irq_intmux_disable = -1;

        // SEQ can't use "flex"
        intr_info[IRQK_MJCP][IRQK_FLEXIBLELINE].irq_num = -1;
        intr_info[IRQK_MJCP][IRQK_FLEXIBLELINE].irq_intmux_enable = -1;
        intr_info[IRQK_MJCP][IRQK_FLEXIBLELINE].irq_intmux_disable = -1;

        intr_info[IRQK_HDVICP0][IRQK_FLEXIBLELINE].irq_num = -1;
        intr_info[IRQK_HDVICP0][IRQK_FLEXIBLELINE].irq_intmux_enable = -1;
        intr_info[IRQK_HDVICP0][IRQK_FLEXIBLELINE].irq_intmux_disable = -1;

        intr_info[IRQK_HDVICP1][IRQK_FLEXIBLELINE].irq_num = -1;
        intr_info[IRQK_HDVICP1][IRQK_FLEXIBLELINE].irq_intmux_enable = -1;
        intr_info[IRQK_HDVICP1][IRQK_FLEXIBLELINE].irq_intmux_disable = -1;

        intr_info[IRQK_NSF][IRQK_FIXEDLINE].irq_num = IRQ_DM365_INSFINT;
        intr_info[IRQK_NSF][IRQK_FIXEDLINE].irq_intmux_enable = DM365_INT_NSF_ENABLE;
        intr_info[IRQK_NSF][IRQK_FIXEDLINE].irq_intmux_disable = DM365_INT_NSF_DISABLE;

        intr_info[IRQK_IMX0][IRQK_FIXEDLINE].irq_num = IRQ_DM365_IMXINT0;
        intr_info[IRQK_IMX0][IRQK_FIXEDLINE].irq_intmux_enable = DM365_INT_IMX0_ENABLE;
        intr_info[IRQK_IMX0][IRQK_FIXEDLINE].irq_intmux_disable = DM365_INT_IMX0_DISABLE;

        intr_info[IRQK_IMX1][IRQK_FIXEDLINE].irq_num = IRQ_DM365_IMXINT1;
        intr_info[IRQK_IMX1][IRQK_FIXEDLINE].irq_intmux_enable = DM365_INT_IMX1_ENABLE;
        intr_info[IRQK_IMX1][IRQK_FIXEDLINE].irq_intmux_disable = DM365_INT_IMX1_DISABLE;

        intr_info[IRQK_MJCP][IRQK_FIXEDLINE].irq_num = IRQ_ASQINT;
        intr_info[IRQK_MJCP][IRQK_FIXEDLINE].irq_intmux_enable = -1;
        intr_info[IRQK_MJCP][IRQK_FIXEDLINE].irq_intmux_disable = -1;

        intr_info[IRQK_HDVICP0][IRQK_FIXEDLINE].irq_num = IRQ_DM365_KLD_ARMINT;
        intr_info[IRQK_HDVICP0][IRQK_FIXEDLINE].irq_intmux_enable = DM365_INT_HDVICP_ENABLE;
        intr_info[IRQK_HDVICP0][IRQK_FIXEDLINE].irq_intmux_disable = DM365_INT_HDVICP_DISABLE;

        intr_info[IRQK_HDVICP1][IRQK_FIXEDLINE].irq_num = -1;
        intr_info[IRQK_HDVICP1][IRQK_FIXEDLINE].irq_intmux_enable = -1;
        intr_info[IRQK_HDVICP1][IRQK_FIXEDLINE].irq_intmux_disable = -1;
#endif  /* defined(LSP_210) */
    }
    else if (cpu_is_davinci_dm644x()) {
        __D("cpu is dm644x\n");
        __E("IRQK not supported for DM644x\n");

        return -EINVAL;
    }
    else {
        __E("Unknown processor type, IRQK not initialized\n");

        return -EINVAL;
    }

    irq_major = register_chrdev(0, "irqk", &irq_fxns);

    if (irq_major < 0) {
        __E("Failed to allocate major number.\n");
        return -ENODEV;
    }

    __D("Allocated major number: %d\n", irq_major);

#if (USE_UDEV==1)

#ifdef USE_CLASS_SIMPLE
    irq_class = class_simple_create(THIS_MODULE, "irqk");
#else
    irq_class = class_create(THIS_MODULE, "irqk");
#endif // USE_CLASS_SIMPLE

    if (IS_ERR(irq_class)) {
        __E("Error creating irq device class.\n");
        return -EIO;
    }

#ifdef USE_CLASS_SIMPLE
    class_simple_device_add(irq_class, MKDEV(irq_major, 0), NULL, "irqk");
#else
#ifdef USE_CLASS_DEVICE
    class_device_create(irq_class, NULL, MKDEV(irq_major, 0), NULL, "irqk");
#else
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,27)
    device_create(irq_class, NULL, MKDEV(irq_major, 0), NULL, "irqk");
#else
    device_create(irq_class, NULL, MKDEV(irq_major, 0), "irqk");
#endif // LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,27)
#endif // USE_CLASS_DEVICE
#endif // USE_CLASS_SIMPLE

#endif // USE_UDEV==1

    for (i = 0; i < IRQK_NUMCHANNELS; i++) {
        channelp = &channels[i];
        init_MUTEX(&channelp->resource_sem);
        channelp->transfer_complete = 0;
        channelp->resource = IRQK_NONE;
        INIT_LIST_HEAD(&channelp->users);
    }

    mutex_init(&irq_mutex);

    printk(KERN_INFO "irqk initialized\n");

    return 0;
}

static void __exit irqk_exit(void)
{
    struct intrinfo *info;
    struct list_head *registeredlistp;
    struct list_head *unext;
    struct list_head *u;
    struct registered_user *user;
    int irq;
    int i;

    __D("In irqk_exit()\n");

    for (i = 0; i < IRQK_NUMRESOURCES; i++) {
        if (registered_resource[i] != NULL) {
            info = registered_resource[i];
            irq = info->irq_num;
            registeredlistp = &channels[irq].users;
            u = registeredlistp->next;

            while (u != registeredlistp) {
                unext = u->next;
                user = list_entry(u, struct registered_user, element);

                __D("Removing file %p from user list of IRQ #%d...\n",
                    user->filp, irq);

                list_del(u);
                kfree(user);

                u = unext;
            }

            __D("close: force freeing busy IRQ #%d.\n", irq);

            releaseResource(i);
        }
    }

#if !defined(LSP_210)
    if (cpu_is_davinci_dm355() || cpu_is_davinci_dm365()) {
        clk_disable(mjcp_clk);
    }
#endif

#if (USE_UDEV==1)
#ifdef USE_CLASS_SIMPLE
    class_simple_device_remove(MKDEV(irq_major, 0));
    class_simple_destroy(irq_class);
#else
#ifdef USE_CLASS_DEVICE
    class_device_destroy(irq_class, MKDEV(irq_major, 0));
#else
    device_destroy(irq_class, MKDEV(irq_major, 0));
#endif
    class_destroy(irq_class);
#endif
#endif // USE_UDEV

    __D("Unregistering character device irqk\n");

    unregister_chrdev(irq_major, "irqk");

    printk(KERN_INFO "irqk unregistered\n");
}

module_init(irqk_init);
module_exit(irqk_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("(c) Texas Instruments");

/*
 *  @(#) ti.sdo.linuxutils.irq; 1, 0, 0,82; 11-30-2010 18:31:43; /db/atree/library/trees/linuxutils/linuxutils-j02x/src/ xlibrary

 */

