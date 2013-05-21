NAME
	capture_prev_rsz_onthe_fly_bayer:	Capture, preview, Resize &
						Display loopback from Bayer RGB
						source
	capture_prev_rsz_onthe_fly_yuv: 	Capture, preview, Resize &
						Display loopback from YUV source

	capture_prev_rsz_ss_raw_yuv: 		Capture, de-interlace using
						Resizer and display loopback
						from composite input (TVP5146)

	do_preview_resize:			Application to preview & resize

	do_resize_420_420:			Application to resize a YUV 420
						Semi Planar image (NV12)

	do_resize				Application to resize and do
						format conversion from UYVY to
						YUV420 Semi Planar (NV12)

	do_resize_420_420			Application to resize a YUV420
						Semi Planar (NV12) image to
						another YUV420 Semi Planar
						(NV12) image of smaller size.

	display					application to streamon and
						streamoff

SYNOPSIS
	capture_prev_rsz_onthe_fly_bayer
	capture_prev_rsz_onthe_fly_yuv
	capture_prev_rsz_ss_raw_yuv
	do_preview_resize
	do_resize_420_420
	do_resize
	display

DESCRIPTION

capture_prev_rsz_onthe_fly_bayer
--------------------------------

This a loopback application that does capture from a Bayer RGB source such as
MT9T031 and do On the fly mode processing on the data using IPIPE and Resizer
and finally save data to SDRAM on a per frame basis. The Resizer is capable of
doing conversion from UVVY to NV12 format. Appication uses V4L2 API to
configure the capture device and queue/dequeue buffers in a loop.

capture_prev_rsz_onthe_fly_yuv
------------------------------

This a loopback application that does capture from a YUV source such as
TVP5146 or TVP7002 and do On the fly mode processing on the data using IPIPE
and Resizer and finally save data to SDRAM on a per frame basis. There is no
processing done in IPIPE for this type of data, but the capture driver design
requires this to be in the data path of the image. The Resizer is capable of
doing conversion from UVVY to NV12 format. Appication uses V4L2 API to
configure the capture device and queue/dequeue buffers in a loop.

capture_prev_rsz_ss_raw_yuv
---------------------------

This application shows how to de-interlace a YUV interlaced image using Resizer.
This application captures from TVP5146 composite input, pass the video data to
Resizer (one shot or single shot mode). The Resizer input is configured to have
a line length of 4 * width to allow skipping of alternate lines. The height is
configured to be 1/2 of original image height, resulting in the image scaled up
vertically by 2x. This is to support the smooth function at application layer
on a interlaced data.

do_preview_resize
-----------------

This application reads a set of options from the user including the input image
file and then do Preview and Resize on a Bayer RGB data. The example shows how
to use the tuning modules in IPIPE to fine tune the image.

do_resize
---------

This application takes an UYVY image as input and do Resize and format
conversion from UYVY to NV12 (a.k.a YUV 420 Semi planar)

do_resize_420_420
-----------------

This application shows how to Resize the Y-Plane and C-Plane of a YUV 420 SP
(NV12) image using the Resizer hardware. The Resize happens in two stages.
First stage does Resize of Y-Plane and then configure the Resizer driver for
C-plane and does one more Resize operation for C-Plane Resize. This application
takes a 720p NV12 image and resize it to half. ie. the image is resized from
1280x720 to 640x360.

OPTIONS

capture_prev_rsz_onthe_fly_bayer
	-t <0/1> 0 - disable Gamma correction, 1 - enable gamma correction
	-f <0/1> 0 - UYVY, 1 - NV12 (YUV 420 Semi planar) output format
	-i <0/1> 0 - input from MT9T031, 1 - input from MT9P031 (TBD)
	-p <0/1> 0 - disable printing frame number, 1 - enable
	-c <0/1> 0 - disable crop, 1 - enable crop

capture_prev_rsz_onthe_fly_yuv
	-f <0/1> 0 - UYVY, 1 - NV12 (YUV 420 Semi planar) output format
	-p <0/1> 0 - disable printing frame number, 1 - enable
	-h <0/1> 0 - disable frame division, 1 - enable frame division (only
		 for TVP7002 to reduce the fps to 30
	-x <0/1> 0 - display from Resizer-A output, 1 - display from Resizer
		 B output
	-c <0/1> 0 - disable crop, 1 - enable crop
	-i <0/1> 0 - input from TVP5146 Composite, 1 - TVP5146 S-Video and 2
		 TVP7002 Component input
	-r <0/1> 0 - disable resize, 1 - enable resize. Use -w and -u options
		 as well
	-w <width> - width of resized image from resizer output
	-u <height> - height of resized image from resizer output

capture_prev_rsz_ss_raw_yuv
	-f <0/1> - 0 - UYVY , 1 - NV12
	
do_preview_resize
	This is an interractive application.

do_resize_420_420
	Resize a NV12 image using two stages of Resize. First the Y-Plane Resize
	and then the C-Plane Resize.
	-i <input file> - Must be a 1280x720 NV12 image
	-o <output file> - Gets a 640x360 NV12 image
	The output file can be viewed using display utility (with -t option)
	given below.

do_resize
	-i <input file> - file to read. Should be 720p resolution
	-w <width> of the output image
	-h <height> of the output image
	-t <0/1> 0 - UYVY, 1 - NV12 format
display
	-c <channel number> 0 - video2 and 1 - video3
	-f <file> to display
	-w <width> of the input image
	-h <height> of the input image
	-f <input file name>

EXAMPLE USAGE

for MT9T031 capture-display
capture_prev_rsz_onthe_fly_bayer -i0 -f0 -i0 -p1 -c0

for TVP7002 capture-display - no resize
capture_prev_rsz_onthe_fly_yuv -i2 -f0 -p1

for TVP7002 capture-display - Resize 1080i/720p to NTSC resolution and display on
composite output
capture_prev_rsz_onthe_fly_yuv -i2 -r1 -w720 -u480

For TVP5146 capture-display using NV12 format
capture_prev_rsz_ss_raw_yuv -f1

for doing upscale of 720p to 1080p and format conversion of UYVY to NV12
do_resize -i video_720p -w 1920 -h 1080 -t1

for displaying a UYVY image to VID0
display -c0 -w720 -h480 -t0

COPYRIGHT
	Refer to source headers

KNOWN ISSUES

VERSION
	LSP 2.10

CHANGELOG
	2.0

SEE ALSO
