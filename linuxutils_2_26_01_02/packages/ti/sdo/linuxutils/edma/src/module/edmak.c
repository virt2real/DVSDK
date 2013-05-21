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
 * edmak.c
 */
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/dma-mapping.h>

#include <linux/spinlock.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/highmem.h>
#include <linux/pagemap.h>
#include <linux/version.h>

#include <asm/dma.h>
#include <asm/io.h>
#include <asm/system.h>
#include <asm/uaccess.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,26)
#include <asm/arch/dma.h>
#include <asm/arch/edma.h>
#include <asm/hardware.h>
#else
// the following are guesses for the upcoming LSP 2.10 for Linux 2.6.28
#include <mach/hardware.h>
#if defined(LSP_210)
#include <mach/dma.h>
#endif  /* defined(LSP_210) */
#include <mach/edma.h>
#endif

#include "../interface/edma.h"

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


#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,18)

#if defined(LSP_210)
#define BASEADDR EDMA_BASE
#else   /* defined(LSP_210) */
#define BASEADDR 0x01c00000
#endif  /* defined(LSP_210) */
#define QCHMAP(n) EDMA_QCHMAP(n)

#else  /* LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,18) */

#define BASEADDR DAVINCI_DMA_3PCC_BASE
#define QCHMAP(n) (BASEADDR + 0x0200 + ((n) << 2))
#define QDMACH_PARAM_CLR_MASK (0x3fe0u)

#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,18) */

#define NCHAN (EDMA_QDMA7 + 1)

static unsigned int version = EDMA_VERSION;

static struct mutex edma_mutex;

#ifdef USE_CLASS_SIMPLE
static struct class_simple *dma_class;
#else
static struct class *dma_class;
#endif
static int major = 0;

typedef struct {
    struct list_head users;
    int nParam;
    int isParam;
} channelObj;

static channelObj channels[NCHAN];

typedef struct registered_user {
    struct list_head element;
    struct file *filp;
} registered_user;

#ifdef __DEBUG
#define __D(fmt, args...) printk(KERN_DEBUG "EDMAK Debug: " fmt, ## args)
#else
#define __D(fmt, args...)
#endif

#define __E(fmt, args...) printk(KERN_ERR "EDMAK Error: " fmt, ## args)


/* release_channel() must be called with the edma_mutex held */
static void release_channel(int chan)
{
    int localChan;
    int i;

    /*
     * The non-LSP_210 EDMA interface returns a "magic" value that represents
     * the controller number and channel number muxed together in one UInt32.
     * This module doesn't yet support a controller other than 0, however, this
     * function needs to accommodate being called with a controller > 0 since
     * it's called to release a channel on a controller > 0 when the
     * REQUESTDMA ioctl() receives a controller > 0 that it can't handle and
     * needs to clean up after itself.
     */
    /*
     * In order to not be dependent on the LSP #defines, we need to
     * translate our EDMA interface's #defines to the LSP ones.
     */
#if defined(LSP_210)

    localChan = chan;
    if (chan >= EDMA_QDMA0 && chan <= EDMA_QDMA7) {
        __D("  release_channel: translating QDMA channel %d to LSP namespace ...\n", chan);
        localChan = EDMA_QDMA_CHANNEL_0 + (chan - EDMA_QDMA0);
    }

    for (i = 0; i < channels[localChan].nParam; i++) {
        __D("  release_channel: freeing channel %d...\n", localChan + i);

        davinci_free_dma(localChan + i);
    }

    INIT_LIST_HEAD(&channels[localChan].users);
    channels[localChan].nParam = 0;
    channels[localChan].isParam = 0;

#else   /* defined(LSP_210) */

    localChan = EDMA_CHAN_SLOT(chan);
    if (localChan >= EDMA_QDMA0 && localChan <= EDMA_QDMA7) {
        __E("  release_channel: QDMA is not supported: chan %d\n", chan);
                
        return;
    }

    for (i = 0; i < channels[localChan].nParam; i++) {
        if (channels[localChan].isParam) {
            __D("  release_channel: calling edma_free_slot(%d)...\n",
                chan + i);

            edma_free_slot(chan + i);
        }
        else {
            __D("  release_channel: calling edma_free_channel(%d)...\n",
                chan + i);

            edma_clean_channel(chan + i);
            edma_free_channel(chan + i);
        }
    }

    if (EDMA_CTLR(chan) == 0) {
        INIT_LIST_HEAD(&channels[localChan].users);
        channels[localChan].nParam = 0;
        channels[localChan].isParam = 0;
    }

#endif  /* defined(LSP_210) */
}

#ifdef USE_UNLOCKED_IOCTL
static long dma_ioctl(struct file *filp, unsigned int cmd, unsigned long args)
#else
static int dma_ioctl(struct inode *inode, struct file *filp,
                     unsigned int cmd, unsigned long args)
#endif
{
    unsigned int __user *argp = (unsigned int __user *) args;
    int isParam = 0;
#if defined(LSP_210)
    int isQdma = 0;
#endif  /* defined(LSP_210) */
    int result;
    int dev_id;
    int channel;
    struct EDMA_requestDmaParams dma_req;
    struct EDMA_releaseDmaParams dma_rel;
    struct list_head *registeredlistp;
    struct list_head *u;
    struct list_head *unext;
    struct registered_user *user;

    if (_IOC_TYPE(cmd) != _IOC_TYPE(EDMA_IOCMAGIC)) {
        __E("dma_ioctl(): bad command type 0x%x (should be 0x%x)\n",
            _IOC_TYPE(cmd), _IOC_TYPE(EDMA_IOCMAGIC));
    }

    switch (cmd & EDMA_IOCCMDMASK) {

      case EDMA_IOCREQUESTDMA:
        __D("dma_ioctl(): EDMA_IOCREQUESTDMA called\n");

        if (copy_from_user(&dma_req, argp, sizeof(dma_req))) {
            return -EFAULT;
        }

        __D("dev_id: %d, eventq_no: %d, tcc: %d, param: %d, nParam: %d\n",
            dma_req.dev_id, dma_req.eventq_no, dma_req.tcc,
            dma_req.param, dma_req.nParam);

        dev_id = dma_req.dev_id;

        /*
         * In order to not be dependent on the LSP #defines, we need to
         * translate our EDMA interface's #defines to the LSP ones.
         */
        if (dev_id >= EDMA_QDMA0 && dev_id <= EDMA_QDMA7) {
#if defined(LSP_210)
            dev_id = EDMA_QDMA_CHANNEL_0 + (dev_id - EDMA_QDMA0);
            isQdma = 1;
#else   /* defined(LSP_210) */
            __E("%s: REQUESTDMA failed: QDMA is not supported\n",
                __FUNCTION__);

            return -EINVAL;
#endif  /* defined(LSP_210) */
        }
        else {
            switch (dev_id) {
              case EDMA_PARAMANY:
                dev_id = EDMA_CONT_PARAMS_ANY;
                isParam = 1;
                break;

              case EDMA_PARAMFIXEDEXACT:
                dev_id = EDMA_CONT_PARAMS_FIXED_EXACT;
                isParam = 1;
                break;

              case EDMA_PARAMFIXEDNOTEXACT:
                dev_id = EDMA_CONT_PARAMS_FIXED_NOT_EXACT;
                isParam = 1;
                break;

              case EDMA_EDMAANY:
#if defined(LSP_210)
                dev_id = EDMA_DMA_CHANNEL_ANY;
#else   /* defined(LSP_210) */
                dev_id = EDMA_CHANNEL_ANY;
#endif  /* defined(LSP_210) */
                break;

              case EDMA_QDMAANY:
#if defined(LSP_210)
                dev_id = EDMA_QDMA_CHANNEL_ANY;
                isQdma = 1;
                break;
#else   /* defined(LSP_210) */
                __E("%s: REQUESTDMA failed: QDMA is not supported\n",
                    __FUNCTION__);
                return -EINVAL;
#endif  /* defined(LSP_210) */

              default:
                /* do nothing, dev_id is an EDMA channel # */
                break;
            }
        }

#if defined(LSP_210)
        switch (dma_req.tcc) {
            case EDMA_TCCANY:
                dma_req.tcc = EDMA_TCC_ANY;
                break;

            case EDMA_TCCSYMM:
                dma_req.tcc = EDMA_TCC_SYMM;
                break;

            default:
                /* do nothing, tcc is an EDMA TCC # */
                break;
        }
#endif  /* defined(LSP_210) */

        if (isParam) {
#if defined(LSP_210)
            __D("calling davinci_request_params(%d, %d, %d)...\n", dev_id,
                dma_req.nParam, dma_req.param);
            result = davinci_request_params(dev_id, dma_req.nParam,
                                            dma_req.param);

            __D("...returned %d\n", result);

            if (result >= 0) {
                dma_req.channel = result;
                dma_req.param = result;
                /* transform to 0-based success for below common code */
                result = 0;
            }

#else   /* defined(LSP_210) */

            __D("calling edma_alloc_cont_slots(0, %d, %d, %d)...\n",
                dev_id, dma_req.param, dma_req.nParam);
            result = edma_alloc_cont_slots(0, dev_id, dma_req.param, dma_req.nParam);

            __D("...returned %d\n", result);

            if (result >= 0) {
                if (EDMA_CTLR(result) != 0) {
                    __E("%s: REQUESTDMA failed to obtain a channel from controller 0 (obtained channel %d from controller %d)\n", __FUNCTION__, EDMA_CHAN_SLOT(result), EDMA_CTLR(result));

                    release_channel(result);
                }
                else {
                    dma_req.channel = EDMA_CHAN_SLOT(result);
                    dma_req.param = dma_req.channel;
                    /* transform to 0-based success for below common code */
                    result = 0;
                }
            }
#endif  /* defined(LSP_210) */
        }
        else {

#if defined(LSP_210)
            if (dma_req.tcc == -1) {
                __E("%s: REQUESTDMA failed: TCC -1 supported only for PaRAM allocations\n", __FUNCTION__);

                return -EINVAL;
            }

            result = davinci_request_dma(dev_id, "linuxutils DMA",
                                         NULL, (void *)NULL,
                                         &dma_req.channel, &dma_req.tcc,
                                         dma_req.eventq_no);

#else   /* defined(LSP_210) */

            result = edma_alloc_channel(dev_id, NULL, NULL, dma_req.eventq_no);

            if (result >= 0) {
                if (EDMA_CTLR(result) != 0) {
                    __E("%s: REQUESTDMA failed to obtain a channel from controller 0 (obtained channel %d from controller %d, will now free it)\n", __FUNCTION__, EDMA_CHAN_SLOT(result), EDMA_CTLR(result));

                    release_channel(result);
                }
                else {
                    dma_req.channel = EDMA_CHAN_SLOT(result);
                    dma_req.tcc = dma_req.channel;
                    /* transform to 0-based success for below common code */
                    result = 0;
                }
            }
#endif  /* defined(LSP_210) */
        }

        if (result) {
            __E("%s: REQUESTDMA failed: %d\n", __FUNCTION__, result);

            return -ENOMEM;
        }
        else {
            /* For EDMA_PARAMANY we've already assigned dma_req.param above */
            if (!isParam) {
#if defined(LSP_210)
                dma_req.param = davinci_get_param(dma_req.channel);
#else   /* defined(LSP_210) */
                dma_req.param = dma_req.channel; /* one-to-one mapping */
#endif  /* defined(LSP_210) */
            }

#if defined(LSP_210)
            /* Translate LSP's QDMA #s to linuxutil's QDMA #s */
            if (isQdma) {
                dma_req.channel = (dma_req.channel - EDMA_QDMA_CHANNEL_0) +
                                  EDMA_QDMA0;
            }
#endif  /* defined(LSP_210) */

            __D("  dma channel %d allocated\n", dma_req.channel);

            __D("copying to user\n");

            if (copy_to_user(argp, &dma_req, sizeof(dma_req))) {
                return -EFAULT;
            }
        }

        user = kmalloc(sizeof(struct registered_user), GFP_KERNEL);
        if (!user) {
            __E("%s: REQUESTDMA failed to kmalloc registered_user struct",
                __FUNCTION__);

            release_channel(dma_req.channel);

            return -ENOMEM;
        }

        if (mutex_lock_interruptible(&edma_mutex)) {
            kfree(user);

            release_channel(dma_req.channel);

            return -ERESTARTSYS;
        }

        user->filp = filp;
        list_add(&user->element, &channels[dma_req.channel].users);

        if (isParam) {
            channels[dma_req.channel].nParam = dma_req.nParam;
            channels[dma_req.channel].isParam = 1;
        }
        else {
            channels[dma_req.channel].nParam = 1;
            channels[dma_req.channel].isParam = 0;
        }

        mutex_unlock(&edma_mutex);

        break;

      case EDMA_IOCREGUSER:
        __D("dma_ioctl(): EDMA_IOCREGUSER called\n");

        if (get_user(channel, argp)) {
            return -EFAULT;
        }

        __D("  channel %d\n", channel);

        if (channel >= NCHAN) {
            __E("%s: REGUSER failed: channel %d out of range\n",
                __FUNCTION__, channel);

            return -ERANGE;
        }

        registeredlistp = &channels[channel].users;
        if (registeredlistp != registeredlistp->next) {
            user = kmalloc(sizeof(struct registered_user), GFP_KERNEL);
            if (!user) {
                __E("%s: REGUSER failed to kmalloc registered_user struct",
                    __FUNCTION__);
                return -ENOMEM;
            }

            if (mutex_lock_interruptible(&edma_mutex)) {
                kfree(user);

                return -ERESTARTSYS;
            }

            user->filp = filp;
            list_add(&user->element, &channels[channel].users);

            mutex_unlock(&edma_mutex);
        }
        else {
            __E("%s: REGUSER failed: channel %d not currently allocated\n",
                __FUNCTION__, channel);

            return -EFAULT;
        }

        break;

      case EDMA_IOCRELEASEDMA:
        __D("dma_ioctl(): EDMA_IOCRELEASEDMA called\n");

        if (copy_from_user(&dma_rel, argp, sizeof(dma_rel))) {
            return -EFAULT;
        }

        __D("  channel %d\n", dma_rel.channel);

        channel = dma_rel.channel;
        if (channel >= NCHAN) {
            __E("%s: REGUSER failed: channel %d out of range\n",
                __FUNCTION__, channel);

            return -ERANGE;
        }

        if (mutex_lock_interruptible(&edma_mutex)) {
            return -ERESTARTSYS;
        }

        registeredlistp = &channels[channel].users;
        u = registeredlistp->next;
        while (u != registeredlistp) {
            unext = u->next;

            user = list_entry(u, struct registered_user, element);
            if (user->filp == filp) {
                __D("  removing registered user from channel %d list\n",
                    channel);

                list_del(u);
                kfree(user);

                /*
                 * Only remove once (we allow multiple "registers", and each
                 * one requires a corresponding "release").
                 */
                break;
            }

            u = unext;
        }

        mutex_unlock(&edma_mutex);

        if (u == registeredlistp) {
            __E("%s: RELEASEDMA failed: file %p not registered for channel %d\n",
                __FUNCTION__, filp, channel);

            return -EFAULT;
        }

        if (mutex_lock_interruptible(&edma_mutex)) {
            return -ERESTARTSYS;
        }

        if (registeredlistp->next == registeredlistp) {
            __D("  no more registered users, freeing channel %d\n", channel);

            release_channel(channel);
        }

        mutex_unlock(&edma_mutex);

        break;

      case EDMA_IOCGETVERSION:
        __D("GETVERSION ioctl received, returning %#x.\n", version);

        if (put_user(version, argp)) {
            return -EFAULT;
        }

        break;

      case EDMA_IOCGETBASEPHYSADDR:
        __D("GETBASEPHYSADDR ioctl received, returning %#x.\n", BASEADDR);

        if (put_user(BASEADDR, argp)) {
            __E("%s: GETBASEPHYSADDR: put_user() failed, returning -EFAULT!\n",
                __FUNCTION__);

            return -EFAULT;
        }

        break;
    }

    return 0;
}

static int release(struct inode *inode, struct file *filp)
{
    struct list_head *u;
    struct list_head *unext;
    struct list_head *registeredlistp;
    struct registered_user *user;
    int found_user;
    int i;

    __D("close: called.\n");

    for (i = 0; i < NCHAN; i++) {
        found_user = 0;

        if (mutex_lock_interruptible(&edma_mutex)) {
            return -ERESTARTSYS;
        }

        registeredlistp = &channels[i].users;
        u = registeredlistp->next;
        while (u != registeredlistp) {
            unext = u->next;

            user = list_entry(u, struct registered_user, element);
            if (user->filp == filp) {
                __D("  removing registered user from channel %d list\n", i);

                found_user = 1;
                list_del(u);
                kfree(user);
            }

            u = unext;
        }

        if (found_user) {
            if (registeredlistp->next == registeredlistp) {
                __D("  no more registered users, freeing channel %d\n", i);

                release_channel(i);
            }
        }

        mutex_unlock(&edma_mutex);
    }

    __D("close: returning\n");

    return 0;
}

static struct file_operations fops = {
#ifdef USE_UNLOCKED_IOCTL
    unlocked_ioctl: dma_ioctl,
#else
    ioctl:   dma_ioctl,
#endif
    owner: THIS_MODULE,
    release: release,
};


static void banner(void)
{
    printk(KERN_INFO "EDMAK module: built on " __DATE__ " at " __TIME__ "\n");
    printk(KERN_INFO "  Reference Linux version %d.%d.%d\n",
           (LINUX_VERSION_CODE & 0x00ff0000) >> 16,
           (LINUX_VERSION_CODE & 0x0000ff00) >> 8,
           (LINUX_VERSION_CODE & 0x000000ff) >> 0
          );
    printk(KERN_INFO "  File " __FILE__ "\n");
}

static int __init mod_init(void)
{
    int i;

    banner();

    major = register_chrdev(0, "edma", &fops);

    __D("edma registered major = %d\n", major);

#ifdef USE_CLASS_SIMPLE
    dma_class = class_simple_create(THIS_MODULE, "edma");
    class_simple_device_add(dma_class, MKDEV(major, 0), NULL, "edma");
#else
#ifdef USE_CLASS_DEVICE
    dma_class = class_create(THIS_MODULE, "edma");
    class_device_create(dma_class, NULL, MKDEV(major, 0), NULL, "edma");
#else
    dma_class = class_create(THIS_MODULE, "edma");
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,27)
    device_create(dma_class, NULL, MKDEV(major, 0), NULL, "edma");
#else
    device_create(dma_class, NULL, MKDEV(major, 0), "edma");
#endif // LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,27)
#endif // USE_CLASS_DEVICE
#endif // USE_CLASS_SIMPLE

    __D("initializing channel owner array...\n");

    for (i = 0; i < NCHAN; i++) {
        INIT_LIST_HEAD(&channels[i].users);
        channels[i].nParam = 0;
        channels[i].isParam = 0;
    }

    mutex_init(&edma_mutex);

    return 0;
}

static void __exit mod_exit(void)
{
    struct list_head *u;
    struct list_head *unext;
    struct list_head *registeredlistp;
    struct registered_user *user;
    int found_user;
    int i;

#ifdef USE_CLASS_SIMPLE
    class_simple_device_remove(MKDEV(major, 0));
    class_simple_destroy(dma_class);
#else
#ifdef USE_CLASS_DEVICE
    class_device_destroy(dma_class, MKDEV(major, 0));
#else
    device_destroy(dma_class, MKDEV(major, 0));
#endif // USE_CLASS_DEVICE
    class_destroy(dma_class);
#endif // USE_CLASS_SIMPLE

    unregister_chrdev(major, "edma");

    /*
     * Free all "owned" channels now.  They're supposed to get either
     * explicitly freed, or auto-freed when the file descriptor for
     * this device driver is closed by a process (which itself might happen
     * during auto-close if the process doesn't explicitly close the file
     * descriptor), but a process might crash or otherwise not get to the
     * auto-close point.  The following code will run when the module is
     * removed from the kernel (w/ rmmod).
     */
    for (i = 0; i < NCHAN; i++) {
        found_user = 0;

        if (mutex_lock_interruptible(&edma_mutex)) {
            return;
        }

        registeredlistp = &channels[i].users;
        u = registeredlistp->next;
        while (u != registeredlistp) {
            found_user = 1;

            unext = u->next;

            user = list_entry(u, struct registered_user, element);
            list_del(u);
            kfree(user);

            u = unext;
        }

        if (found_user) {
            release_channel(i);
        }

        mutex_unlock(&edma_mutex);
    }

    __D("edma unregistered\n");
}

module_init(mod_init);
module_exit(mod_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Texas Instruments");
MODULE_DESCRIPTION("DMA operations from user mode");

/*
 *  @(#) ti.sdo.linuxutils.edma; 1, 0, 0,92; 11-30-2010 18:31:36; /db/atree/library/trees/linuxutils/linuxutils-j02x/src/ xlibrary

 */

