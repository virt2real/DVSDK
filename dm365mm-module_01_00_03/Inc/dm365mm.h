/**
 * @file    Ddm365mm.h 
 * @brief   Describes the interface to the dm350mm module.
 * @version alpha3
 *
 * The dm350mm library which this header file interfaces had a kernel module
 * associated with it (dm350mmap.ko), which needs to be loaded if calls to this
 * library are not to fail.
 *
 * The module is inserted like, for instance:
 * 
 * @verbatim /sbin/insmod dm350mmap.ko  @endverbatim
 *
 * @verbatim
 * ============================================================================
 * Copyright (c) Texas Instruments Inc 2007
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied or provided.
 * ============================================================================
 * @endverbatim
 */

#ifndef _DM360MM_H
#define _DM365MM_H

#include <sys/types.h>

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief Initialize the DM365MM module. Must be called before other API calls.
 * @return 0 for success or -1 for failure.
 */
    int DM365MM_init(void);


/**
 * @brief Finalize the DM365MM module. After this function has been called,
 * no other DM365MM function may be called (unless DM365MM is reinitialized).
 * @return 0 for success or -1 for failure.
 */
    int DM365MM_exit(void);

/**
 * @brief Set PID of the process to send SEQ interrupt (ASQINT) 
 * @return 0 for success or -1 for failure.
 */
    int DM365MM_setPid(pid_t pid);

/**
 * @brief Map user space virtual address for given physical address region
 * @return virtual address for success or -1 for failure.
 */

    void *DM365MM_mapVirt(unsigned long phys, unsigned int len);

/**
 * @brief Unmap user space virtual address
 * @return 0 for success or -1 for failure.
 */

    int DM365MM_unmapVirt(void *ptr, unsigned int len);

/**
 * @brief Memcpy using EDMA
 * @return 0 for success or -1 for failure.
 */

    int DM365MM_memcpy (void *dst, void *src, unsigned int srcwidth,unsigned int width, unsigned int height, unsigned int dstwidth);

/**
 * @brief Wait for sequencer operation to finish
 * @return 0 for success or negative for failure. (Process interrupted/abort etc)
 */
	int DM365MM_waitForSequencer();
/**
 * @brief Clear any pending interrupts.
 * @return 0 for success or negative for failure. 
 */
	int DM365MM_clearPending(void);

#if defined (__cplusplus)
}
#endif
#endif                          // _DM365MM_H
