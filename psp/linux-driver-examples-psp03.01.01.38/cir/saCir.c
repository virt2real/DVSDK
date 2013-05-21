/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|         Copyright (c) 1998-2009 Texas Instruments Incorporated           |**
**|                        ALL RIGHTS RESERVED                               |**
**|                                                                          |**
**| Permission is hereby granted to licensees of Texas Instruments           |**
**| Incorporated (TI) products to use this computer program for the sole     |**
**| purpose of implementing a licensee product based on TI products.         |**
**| No other rights to reproduce, use, or disseminate this computer          |**
**| program, whether in part or in whole, are granted.                       |**
**|                                                                          |**
**| TI makes no representation or warranties with respect to the             |**
**| performance of this computer program, and specifically disclaims         |**
**| any responsibility for any damages, special or consequential,            |**
**| connected with the use of this program.                                  |**
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <linux/types.h>

#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/cir.h>

/* Define the following macro if the reads needs to block */
#define CIR_READ_BLOCKS 1

int main(int argc, char *argv[])
{
int cir_fd;
int cnt;
__u16 buf;
int ret_val;
int time_val = 200;


#ifdef CIR_READ_BLOCKS
cir_fd = open("/dev/cir", O_RDONLY, 0);
#else  /* CIR_READ_BLOCKS */
cir_fd = open("/dev/cir", O_RDONLY | O_NONBLOCK, 0);
#endif /* CIR_READ_BLOCKS */


	if (cir_fd <= 0) {
		printf ("Unable to open the CIR device\n");
		return -1;
	}

	ret_val = ioctl(cir_fd, CIR_SET_REPEAT_DELAY, &time_val);

	if (ret_val != time_val) {
		printf ("Unable to set the repeat delay of the driver. Driver"\
		"might continue to use the default value set.\n");
	} else {
		time_val = 0;
		if (ioctl(cir_fd, CIR_GET_REPEAT_DELAY, &time_val) != 0) {
			printf ("Ioctl: CIR_GET_REPEAT_DELAY Failed\n");
	}
}

printf("+******************************************************************+\n");
printf("| Use an RC-5 remote and press the keys on the remote. The keys or |\n");
printf("| the keycodes (RC-5) are displayed on the screen.                 |\n");
printf("| The program loops till the power button is pressed on the remote |\n");
printf("| (or 100 keys are pressed on the remote, when operating in        |\n");
printf("| blocking mode or for 100 seconds or 100 keys are pressed,        |\n");
printf("| whichever is earlier, if the application works in non-blocking   |\n");
printf("| mode.)                                                           |\n");
printf("| The program can also be interrupted by pressing Ctrl+C anytime.  |\n");
printf("+******************************************************************+\n");

while (cnt != 100) {
	if (read(cir_fd, &buf, sizeof(__u16)) < 0) {
		if (errno != EAGAIN) {
			printf("Unable to read from the CIR device\n");
		break;
	}
	} else {
		switch (buf & 0x07FF) {
		case 0x0000:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Number 0\n");
		break;

		case 0x0001:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Number 1\n");
		break;

		case 0x0002:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Number 2\n");
		break;

		case 0x0003:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Number 3\n");
		break;

		case 0x0004:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Number 4\n");
		break;

		case 0x0005:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Number 5\n");
		break;

		case 0x0006:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Number 6\n");
		break;

		case 0x0007:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Number 7\n");
		break;

		case 0x0008:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Number 8\n");
		break;

		case 0x0009:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Number 9\n");
		break;

		case 0x0022:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Enter or ");
		printf("Prev Chan or Repeat Key\n");
		break;

		case 0x00EC:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("TV/VCR or Input Key\n");
		break;

		case 0x000F:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Select or Info or ");
		printf("Mute or OK key\n");
		break;

		case 0x002E:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Menu or In/Out Key\n");
		break;

		case 0x001E:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("CC or Subtitle Key\n");
		break;

		case 0x0020:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Channel Up Key\n");
		break;

		case 0x0021:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Channel Down Key\n");
		break;

		case 0x0010:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Volume + Key\n");
		break;

		case 0x0011:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Volume - Key\n");
		break;

		case 0x0169:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Pause Key\n");
		break;

		case 0x0177:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Record Key\n");
		break;

		case 0x0172:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Scan-/Rew Key\n");
		break;

		case 0x0174:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Scan+/Fwd Key\n");
		break;

		case 0x0175:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Play Key\n");
		break;

		case 0x0176:
		printf("Key [%d - 0x%04x] = ", cnt+1, buf & 0x07FF);
		printf("Stop Key\n");
		break;

		case 0x00C:
		printf("You pressed the POWER key\n");
		printf("Powering off the application !!\n");
		return 0;

		default:
		ioctl(cir_fd, CIR_FLUSH);
		cnt--;
		break;
		}
	}

	fflush(stdout);
	cnt++;
	#ifndef CIR_READ_BLOCKS
	usleep(1000000);
	#endif
	}

return 0;
}

