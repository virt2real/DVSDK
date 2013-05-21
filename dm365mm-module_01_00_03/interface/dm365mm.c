/*
 * dm365mm.c
 *
 * ============================================================================
 * Copyright (c) Texas Instruments Inc 2007
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied or provided.
 * ============================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
//#include <ti/sdo/ce/osal/Memory.h>

#include <dm365mm.h>
//#include <cmem.h>
typedef struct _edma_params
{
  unsigned long src;
   unsigned long dst;
   unsigned int srcmode;
   unsigned int srcfifowidth;
   int srcbidx;
   int srccidx;
   unsigned int dstmode;
   unsigned int dstfifowidth;
   int dstbidx;
   int dstcidx;
   int acnt;
   int bcnt;
   int ccnt;
   int bcntrld;
   int syncmode;
 } edma_params;


#define DM365MMAP_IOCMEMCPY         0x7
#define DM365MMAP_IOCWAIT           0x8
#define DM365MMAP_IOCCLEAR_PENDING  0x9

#ifdef __DEBUG
#define __D(fmt, args...) fprintf(stderr, "DM365MM Debug: " fmt, ## args)
#else /*  */
#define __D(fmt, args...)
#endif  /*  */

#ifdef __DEBUG
#define __E(fmt, args...) fprintf(stderr, "DM365MM Error: " fmt, ## args)
#else /*  */
#define __E(fmt, args...)
#endif  /*  */
static int dm365mm_fd = -1;
static int refcount = 0;


int DM365MM_init (void)
{
  if (refcount == 0)

    {
      dm365mm_fd = open ("/dev/dm365mmap", O_RDWR | O_SYNC);  //O_SYNC is essential
      if (dm365mm_fd == -1)

  {
    __E ("init: Failed to open /dev/dm365mmap.\n");
    return -1;
  }
    }
  refcount++;
  printf("\r\n DM365MM Init Successful");
  return 0;
}


int DM365MM_exit (void)
{
  int result = 0;
  if (dm365mm_fd == -1)
    {
      __E ("exit: You must initialize DM365MM before making API calls.\n");
      return -1;
    }
  refcount--;
  if (refcount == 0)

    {
      result = close (dm365mm_fd);
      dm365mm_fd = -1;
    }
  return result;
}


int DM365MM_clearPending (void)
{
  if (dm365mm_fd == -1)
    {
      __E ("clearPending: invalid fd\n");
      return -1;
    }
  if (ioctl (dm365mm_fd, DM365MMAP_IOCCLEAR_PENDING, NULL) == -1)
    {
      __E ("clearPending: Clear Pending failed.\n");
      return -1;
    }
  return 0;
}


int DM365MM_waitForSequencer (void)
{
  if (dm365mm_fd == -1)
    {
      __E ("waitForSequencer: invalid fd\n");
      return -1;
    }
  if (ioctl (dm365mm_fd, DM365MMAP_IOCWAIT, NULL) == -1)
    {
      __E
  ("waitForSequencer: Wait failed, process interrupted in between.\n");
      return -1;
    }
  return 0;
}

int DM365MM_memcpy (void *dst, void *src, unsigned int srcwidth,unsigned int width,
    unsigned int height, unsigned int dstwidth)
{
  edma_params edmaparams;
//  printf("CPY");
  if (dm365mm_fd == -1)
    {
      __E ("memcpy: You must initialize DM365MM before making API calls.\n");
      return -1;
    }
//	printf("src = %x,dst = %x srcwidth= %d src height= %d dstwidth= %d\n",src,dst,srcwidth,height,dstwidth);
  edmaparams.srcmode = 0; //INC mode
  edmaparams.srcfifowidth = 0;  //Don't care
  edmaparams.srcbidx = srcwidth;
  edmaparams.srccidx = srcwidth * height;
  edmaparams.dstmode = 0; //INC mode
  edmaparams.dstfifowidth = 0;  //Don't care
  edmaparams.dstbidx = dstwidth;
  edmaparams.dstcidx = dstwidth * height;
  edmaparams.src = CMEM_getPhys (src);
  edmaparams.dst = CMEM_getPhys (dst);
//  edmaparams.src = Memory_getBufferPhysicalAddress (src,srcwidth * height);
//  edmaparams.dst = Memory_getBufferPhysicalAddress (dst,dstwidth * height);
  edmaparams.acnt = width;// Anand 1215 srcwidth;
  edmaparams.bcnt = height;
  edmaparams.ccnt = 1;
  edmaparams.bcntrld = height;  //important setting
  edmaparams.syncmode = 1;  //AB-Sync

  if (ioctl (dm365mm_fd, DM365MMAP_IOCMEMCPY, &edmaparams) == -1)
    {
      __E ("memcpy: Failed to do memcpy\n");
      return -1;
    }
  return 0;
}

