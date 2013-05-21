File Name:
	yuv_multipass_resize.c

Description:
	This program demonstrates the up scaling by 10x of 16-bit interleaved
	YUV data with help of multipass. For doing 10x downscaling first the
	downscaling upto 4x have been done and than 2.5x up scaling on the
	output image of first resizing.

Input:
	The input to the program is Y,U and V data which is taken from
	yfinaldeci.bin, cbfinaldeci.bin and crfinaldeci.bin. The input
	resolution is 64x64.

Output:
	The output of the program is resized image of resolution 640*640 which
	can be viewed in YUV player. The output file name is 10x_finaloutput.YUV.

Steps to execute:
	Copy the contents present in this folder to the target File system and
	execute the yuv_multipass_resize executable.
