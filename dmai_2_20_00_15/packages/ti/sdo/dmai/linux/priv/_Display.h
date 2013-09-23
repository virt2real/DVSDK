/* --COPYRIGHT--,BSD
 * Copyright (c) 2010, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/

#ifndef ti_sdo_dmai__Display_h_
#define ti_sdo_dmai__Display_h_

//#include <uapi/linux/fb.h>
#if defined(Dmai_Device_omap3530)
#include <linux/omapfb.h>
#endif
/* Interpretation of offset for color fields: All offsets are from the right,
 * inside a "pixel" value, which is exactly 'bits_per_pixel' wide (means: you
 * can use the offset as right argument to <<). A pixel afterwards is a bit
 * stream and is written to video memory as that unmodified.
 *
 * For pseudocolor: offset and length should be the same for all color
 * components. Offset specifies the position of the least significant bit
 * of the pallette index in a pixel value. Length indicates the number
 * of available palette entries (i.e. # of entries = 1 << length).
 */
struct fb_bitfield {
	unsigned long offset;			/* beginning of bitfield	*/
	unsigned long length;			/* length of bitfield		*/
	unsigned long msb_right;		/* != 0 : Most significant bit is */
					/* right */
};
struct fb_var_screeninfo {
	unsigned long xres;			/* visible resolution		*/
	unsigned long yres;
	unsigned long xres_virtual;		/* virtual resolution		*/
	unsigned long yres_virtual;
	unsigned long xoffset;			/* offset from virtual to visible */
	unsigned long yoffset;			/* resolution			*/

	unsigned long bits_per_pixel;		/* guess what			*/
	unsigned long grayscale;		/* 0 = color, 1 = grayscale,	*/
					/* >1 = FOURCC			*/
	struct fb_bitfield red;		/* bitfield in fb mem if true color, */
	struct fb_bitfield green;	/* else only length is significant */
	struct fb_bitfield blue;
	struct fb_bitfield transp;	/* transparency			*/

	unsigned long nonstd;			/* != 0 Non standard pixel format */

	unsigned long activate;			/* see FB_ACTIVATE_*		*/

	unsigned long height;			/* height of picture in mm    */
	unsigned long width;			/* width of picture in mm     */

	unsigned long accel_flags;		/* (OBSOLETE) see fb_info.flags */

	/* Timing: All values in pixclocks, except pixclock (of course) */
	unsigned long pixclock;			/* pixel clock in ps (pico seconds) */
	unsigned long left_margin;		/* time from sync to picture	*/
	unsigned long right_margin;		/* time from picture to sync	*/
	unsigned long upper_margin;		/* time from sync to picture	*/
	unsigned long lower_margin;
	unsigned long hsync_len;		/* length of horizontal sync	*/
	unsigned long vsync_len;		/* length of vertical sync	*/
	unsigned long sync;			/* see FB_SYNC_*		*/
	unsigned long vmode;			/* see FB_VMODE_*		*/
	unsigned long rotate;			/* angle we rotate counter clockwise */
	unsigned long colorspace;		/* colorspace for FOURCC-based modes */
	unsigned long reserved[4];		/* Reserved for future compatibility */
};

typedef struct Display_Object {
    Int                  fd;
    Int                  frameSkip;
    Int                  started;
    Int                  userAlloc;
    Int                  displayIdx;
    Int                  workingIdx;
    Display_Std          displayStd;
    VideoStd_Type        videoStd;
    BufTab_Handle        hBufTab;
    struct _VideoBufDesc *bufDescs;
    struct fb_var_screeninfo origVarInfo;
    Display_Attrs        attrs;
} Display_Object;


extern int _Display_sysfsChange(Display_Output *displayOutput, 
                            char* displayDevice, VideoStd_Type *videoType, 
                            Int *rotation);
extern int _Display_enableDevice(Display_Attrs *attrs, Bool Enable);

#endif // ti_sdo_dmai_Display_h_
