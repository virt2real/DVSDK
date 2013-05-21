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
 * sdmak.c
 */
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/dma-mapping.h>
#include <linux/sched.h>
#include <linux/spinlock.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/highmem.h>
#include <linux/pagemap.h>

#include <asm/dma.h>
#include <asm/io.h>

#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,26)
#include <asm/arch/dma.h>
#include <asm/hardware.h>
#include <asm/arch/tc.h>
#elif LINUX_VERSION_CODE < KERNEL_VERSION(2,6,32)
#include <mach/hardware.h>
#include <mach/dma.h>
#include <mach/tc.h>
#else
#include <plat/hardware.h>
#include <plat/dma.h>
#include <plat/tc.h>
#endif

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

#include "../interface/sdma.h"

struct channel {
    struct SDMA_transferState *ptransferState;
    struct page *ptransferStatePage;
    struct semaphore mutex;
    struct file *owner;
};

#define SDMA_NUMCHANNELS 32
struct channel channels[SDMA_NUMCHANNELS];

static unsigned int version = SDMA_VERSION;

#ifdef USE_CLASS_SIMPLE
static struct class_simple *dma_class;
#else
static struct class *dma_class;
#endif
static int major = 0;

#ifdef __DEBUG
#define __D(fmt, args...) printk(KERN_DEBUG "SDMAK Debug: " fmt, ## args)
#else
#define __D(fmt, args...)
#endif

#define __E(fmt, args...) printk(KERN_ERR "SDMAK Error: " fmt, ## args)

static void dma_callback(int lch, u16 ch_status, void *data)
{
    if (channels[lch].owner != NULL) {
        __D("dma_callback(): lch=0x%x, ch_status=0x%04x, "
            "setting transferCompleted\n", lch, ch_status);

        channels[lch].ptransferState->transferCompleted = 1;

        if (channels[lch].ptransferState->checkPending) {
            __D("  checkPending is set, posting mutex...\n");

            channels[lch].ptransferState->checkPending = 0;
            up(&(channels[lch].mutex));
        }
    }
    else {
        __E("dma_callback(): unexpected event on channel %d\n", lch);
    }
}

static void dma_release_channel(int ch)
{
    omap_free_dma(ch);
    /* NULL owner field only since ISR operates based on owner != NULL */
    channels[ch].owner = NULL;
    /* NULL owner field only since ISR operates based on owner != NULL */
    page_cache_release(channels[ch].ptransferStatePage);
    kunmap(channels[ch].ptransferStatePage);
}


#ifdef USE_UNLOCKED_IOCTL
static long dma_ioctl(struct file *filp, unsigned int cmd, unsigned long args)
#else
static int dma_ioctl(struct inode *inode, struct file *filp,
                     unsigned int cmd, unsigned long args)
#endif
{
    unsigned int __user *argp = (unsigned int __user *) args;
    int result;
    int channel;
    unsigned long ptransferState;
    union SDMA_requestDmaParams dma_req;
    struct page *page;

    if (_IOC_TYPE(cmd) != _IOC_TYPE(SDMA_IOCMAGIC)) {
        __E("ioctl(): bad command type 0x%x (should be 0x%x)\n",
            _IOC_TYPE(cmd), _IOC_TYPE(SDMA_IOCMAGIC));
    }

    switch (cmd & SDMA_IOCCMDMASK) {
      case SDMA_IOCREQUESTDMA:
        __D("dma_ioctl(): SDMA_IOCREQUESTDMA called\n");

        if (copy_from_user(&dma_req, argp, sizeof(dma_req))) {
            return -EFAULT;
        }

        result = omap_request_dma(OMAP_DMA_NO_DEVICE, "DMA Test",
                                  dma_callback, (void *)NULL, &channel);
        if (result) {
            __E("%s: request_dma failed: %d\n", __FUNCTION__, result);

            return -ENOMEM;
        }
        else {
            __D("  dma channel %d allocated\n", channel);

            down_read(&current->mm->mmap_sem);

            if (get_user_pages(current, current->mm,
                               (unsigned long)dma_req.ptransferState,
                               1, 1, 0, &page, NULL) == 1) {

                ptransferState = (unsigned long)kmap(page);
                ptransferState += (unsigned long)dma_req.ptransferState &
                                  (PAGE_SIZE - 1);

                channels[channel].ptransferState =
                  (struct SDMA_transferState *)ptransferState;
                channels[channel].ptransferStatePage = page;

                __D("  user ptransferState=%#lx, kernel ptransferState=%#lx\n",
                    ptransferState, (unsigned long)dma_req.ptransferState);
                __D("  initial completed value: %d\n",
                    ((struct SDMA_transferState *)ptransferState)->transferCompleted);
            }
            else {
                __E("failed to get struct page for user ptransferState %#lx\n",
                    (unsigned long)dma_req.ptransferState);
                __E("  freeing channel %d...\n", channel);

                omap_free_dma(channel);

                up_read(&current->mm->mmap_sem);

                return -EFAULT;
            }

            up_read(&current->mm->mmap_sem);

            init_MUTEX_LOCKED(&(channels[channel].mutex));
            channels[channel].owner = filp;

            if (copy_to_user(argp, &channel, sizeof(channel))) {
                return -EFAULT;
            }
        }

        break;

      case SDMA_IOCRELEASEDMA:
        __D("dma_ioctl(): SDMA_IOCRELEASEDMA called\n");

        if (copy_from_user(&channel, argp, sizeof(channel))) {
            return -EFAULT;
        }

        __D("  freeing channel %d...\n", channel);

        /* should probably check that channels[channel].owner == filp */

        dma_release_channel(channel);

        break;

      case SDMA_IOCWAITFORCOMPLETION:
        __D("dma_ioctl(): SDMA_IOCWAITFORCOMPLETION called\n");

        if (copy_from_user(&channel, argp, sizeof(channel))) {
            return -EFAULT;
        }

        __D("  channel %d\n", channel);

        if (channels[channel].owner == filp) {
            if (down_interruptible(&(channels[channel].mutex))) {
                __D("  wait interrupted, returning\n");
                return -ERESTARTSYS;
            }
            else {
                __D("  ...got it\n");
            }
        }
        else {
            __D("  unowned channel, not waiting\n");
            return -EINVAL;
        }

        break;

      case SDMA_IOCGETVERSION:
        __D("GETVERSION ioctl received, returning %#x.\n", version);

        if (put_user(version, argp)) {
            return -EFAULT;
        }

        break;
    }

    return 0;
}

static int dma_release(struct inode *inode, struct file * filp)
{
    int i;

    for (i = 0; i < SDMA_NUMCHANNELS; i++) {
        if (channels[i].owner == filp) {
            dma_release_channel(i);
        }
    }

    return 0;
}

static struct file_operations fops = {
#ifdef USE_UNLOCKED_IOCTL
    unlocked_ioctl: dma_ioctl,
#else
    ioctl:   dma_ioctl,
#endif
    release: dma_release,
    owner: THIS_MODULE
};

static void banner(void)
{
    printk(KERN_INFO "SDMAK module: built on " __DATE__ " at " __TIME__ "\n");
    printk(KERN_INFO "  Reference Linux version %d.%d.%d\n",
           (LINUX_VERSION_CODE & 0x00ff0000) >> 16,
           (LINUX_VERSION_CODE & 0x0000ff00) >> 8,
           (LINUX_VERSION_CODE & 0x000000ff) >> 0
          );
    printk(KERN_INFO "  File " __FILE__ "\n");
}

static int mod_init(void)
{
    int channel;
    int err = 0;

    banner();

    major = register_chrdev(0, "sdma", &fops);

    __D("sdma registered major = %d\n", major);

#ifdef USE_CLASS_SIMPLE
    dma_class = class_simple_create(THIS_MODULE, "sdma");
#else
    dma_class = class_create(THIS_MODULE, "sdma");
#endif

    if (IS_ERR(dma_class)) {
        __E("Error creating sdma device class.\n");
        err = -EIO;
        goto fail_after_reg;
    }

#ifdef USE_CLASS_SIMPLE
    class_simple_device_add(dma_class, MKDEV(major, 0), NULL, "sdma");
#else
#ifdef USE_CLASS_DEVICE
    class_device_create(dma_class, NULL, MKDEV(major, 0), NULL, "sdma");
#else
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,27)
    device_create(dma_class, NULL, MKDEV(major, 0), NULL, "sdma");
#else
    device_create(dma_class, NULL, MKDEV(major, 0), "sdma");
#endif // LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,27)
#endif // USE_CLASS_DEVICE
#endif // USE_CLASS_SIMPLE

    for (channel = 0; channel < SDMA_NUMCHANNELS; channel++) {
        channels[channel].owner = NULL;
        channels[channel].ptransferState = NULL;
    }

    return 0;

fail_after_reg:
    __D("Unregistering character device sdma\n");
    unregister_chrdev(major, "sdma");

    return err;
}

static void mod_exit(void)
{
    int channel;

    for (channel = 0; channel < SDMA_NUMCHANNELS; channel++) {
        if (channels[channel].owner != NULL) {
            omap_free_dma(channel);
        }
    }

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

    unregister_chrdev(major, "sdma");
    __D("sdma unregistered\n");
}

module_init(mod_init);
module_exit(mod_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Texas Instruments");
MODULE_DESCRIPTION("DMA operations from user mode");

/*
 *  @(#) ti.sdo.linuxutils.sdma; 1, 0, 0,95; 11-30-2010 18:31:50; /db/atree/library/trees/linuxutils/linuxutils-j02x/src/ xlibrary

 */

