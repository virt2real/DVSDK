File Name:
	planar_resize.c

Description:
	This program demonstrates the up scaling by 2x of 8-bit planar data.
	For resizing of 8 bit data, 3 separate channel have been created
	which will do resizing of Y, U and V respectively.

Input:
	The input to the program is YUV data which is taken from yfinaldeci.bin,
	cbfinaldeci.bin and crfinaldeci.bin. The input resolution is 640x480.

Output:
	The output of the program is resized image of resolution 320x240 which
	can be viewed in YUV player. The output file name is 8bitfinaloutput.YUV.

Steps to execute:
	Copy the contents present in this folder to the target File system and
	execute the planar_resize executable.
