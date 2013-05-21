NAME:
	capture_prev_rsz_ss_raw_bayer: Resizer in bayer mode: single
		shot mode, user pointer IO
	capture_prev_rsz_ss_raw_yuv: Resizer in yuv mode:  single
		shot mode, user pointer IO
	capture_prev_rsz_onthe_fly_bayer: Resizer in bayer mode: on-the-fly
		mode, user ptr IO

SYNOPSIS
	capture_prev_rsz_ss_raw_bayer
	capture_prev_rsz_ss_raw_yuv
	capture_prev_rsz_onthe_fly_bayer

DESCRIPTION

capture_prev_rsz_ss_raw_bayer
	This application shows how to preview and resize a bayer RGB image in one
	shot mode. The v4l2 device is configured to use USERPTR IO. The data
	is captured to SDRAM from CCDC. Application DQ the buffer and  pass it to
	preview device which has resizer chained in the data path. The output of
	Resizer-1 is written to SDRAM and is passed to display device to display
	the same in a loopback mode. 	

capture_prev_rsz_ss_raw_yuv
	This application shows how to use Resizer to do de-interlace of an
	interlaced yuv image and display it in a loopback mode. The captured
	image top field is used for the smoothening operation.

capture_prev_rsz_onthe_fly_bayer
	This application shows how to preview and resize a bayer RGB image
	in on-the-fly mode (continuous). The v4l2 device is configured to
	use USERPTR IO. This captures Bayer RGB data from a MT9T031 sensor,
	pass it through CCDC, then to IPIPE and Resizer. The Resizer1 output
	is written to SDRAM. Application DQ the data buffer and pass it to
	display device to display the same in a loopback mode.

OPTIONS

capture_prev_rsz_ss_raw_bayer
	-t <0/1> 0 - disable gamma correction, 1 - enable 
	-f <0/1> 0 - Bayer RGB input
	-p <0/1> 0 - disable printing frame number, 1 - enable
	-i <0/1> 0 - MT9T031 input
	-m <0/1/2/3> - 0 - VGA, 1 - 480p, 2 - 576p, 3 - 720p

capture_prev_rsz_onthe_fly_bayer
	-w <width of the desired image from input>
	-h <height of the desired image from input>
	-t <0/1> 0 - disable gamma correction, 1 - enable 

capture_prev_rsz_ss_raw_yuv
	-i <0> - 0 - capture from TVP7002 composite input

EXAMPLE USAGE

For capture and display 480p image in one shot mode
./capture_prev_rsz_ss_raw_bayer -t1 -f0 -p1 -i1
For capture and display NTSC image in one shot mode
./capture_prev_rsz_ss_raw_yuv -i0
For capture and display 480p image in on the fly mode
./capture_prev_rsz_ss_raw_bayer -t1 -w720 -h480

COPYRIGHT
	Refer to source headers

KNOWN ISSUES

VERSION
	LSP 2.10

CHANGELOG
	2.0

SEE ALSO
       For Video User Guides, see PSP_##_##_##_###/docs directory.
