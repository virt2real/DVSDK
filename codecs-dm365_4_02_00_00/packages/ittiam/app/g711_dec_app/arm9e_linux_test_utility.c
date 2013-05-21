/*****************************************************************************/
/*                                                                           */
/*                            COMMON VQE                                     */
/*                  ITTIAM SYSTEMS PVT LTD, BANGALORE                        */
/*                           COPYRIGHT(C) 2006                               */
/*                                                                           */
/*  This program  is  proprietary to  Ittiam  Systems  Private  Limited  and */
/*  is protected under Indian  Copyright Law as an unpublished work. Its use */
/*  and  disclosure  is  limited by  the terms  and  conditions of a license */
/*  agreement. It may not be copied or otherwise  reproduced or disclosed to */
/*  persons outside the licensee's organization except in accordance with the*/
/*  terms  and  conditions   of  such  an  agreement.  All  copies  and      */
/*  reproductions shall be the property of Ittiam Systems Private Limited and*/
/*  must bear this notice in its entirety.                                   */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/*                                                                           */
/*  File Name         : arm9e_linux_test_utility.c                           */
/*                                                                           */
/*  Description       : This file contains all the necessary examples to     */
/*                      establish a consistent use of Ittiam C coding        */
/*                      standards (based on Indian Hill C Standards)         */
/*                                                                           */
/*  List of Functions :  compute_cycles()                                    */
/*                       profile_algorithm()                                 */
/*                       cache_algorithm()                                   */
/*                       stack_contamination()                               */
/*                       stack_usage()                                       */
/*                                                                           */
/*                                                                           */
/*  Issues / Problems : None                                                 */
/*                                                                           */
/*  Revision History  :                                                      */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*         10 01 2005   Ittiam          Draft                                */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* File Includes                                                             */
/*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "test_utility.h"

#define ARM_CLOCK_DM6446		297 /* in MegaHertz */
#define ARM_CLOCK_DM355         216 /* in MegaHertz */

/* DSP clock frequency for calculating MCPS for remote call */
#define DSP_CLOCK_DM6446        594 /* in MegaHertz */

/*****************************************************************************/
/* Global Variable Definitions                                               */
/*****************************************************************************/
FILE *profile_file = NULL;

/* Globals required for interruptibility testing */
FILE *interruptability_file = NULL;

/* File to store stack usage value in Bytes */
FILE *stack_file = NULL;

/*****************************************************************************/
/* Local constants used                                                      */
/*****************************************************************************/
#define INTERRUPT_FILE  "interrupts.txt"
#define PROFILE_FILE    "profiles.txt"
#define STACK_FILE      "stacks.txt"

/*****************************************************************************/
/* Functions                                                                 */
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*  Function Name : get_time_in_us() 		                                 */
/*                                                                           */
/*  Description   : This function returns time in microseconds 	 			 */
/*                                                                           */
/*  Inputs        : None				         							 */
/*  Globals       : No global variables being used                           */
/*  Processing    : None                                                     */
/*  Outputs       : None                                                     */
/*  Returns       : time in microseconds			                         */
/*  Issues        : None                                                     */
/*                                                                           */
/*  Revision History:                                                        */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*         09 01 2008   Ittiam          First draft                          */
/*                                                                           */
/*****************************************************************************/

static double get_time(void)
{
	struct timeval tv;
	double microseconds;

	if(gettimeofday(&tv, NULL) != 0)
	{
		printf("Error in gettimeofday\n");
		return -1;
	}

	microseconds = (double)((tv.tv_sec * 1000000.0) + (double)tv.tv_usec);
	return microseconds;
}

/*****************************************************************************/
/*                                                                           */
/*  Function Name : profile_algorithm() 	                                 */
/*                                                                           */
/*  Description   : This function can be used for profiling an algo			 */
/*                                                                           */
/*  Inputs        : None				         							 */
/*  Globals       : No global variables being used                           */
/*  Processing    : Writes the profile values in a file                      */
/*  Outputs       : None                                                     */
/*  Returns       : None  			                         			     */
/*  Issues        : None                                                     */
/*                                                                           */
/*  Revision History:                                                        */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*         09 01 2008   Ittiam          First draft                          */
/*                                                                           */
/*****************************************************************************/

void profile_algorithm(COMMAND cmd)
{
    /* Time related variables declared */
	static int frame_count = 0;
    static double start_time, total_time = 0, peak_time = 0;
    double end_time, delta;

    switch(cmd)
    {
    case OPEN:
        if(NULL == (profile_file = fopen(PROFILE_FILE, "w")))
        {
            printf("\nnot able to open profile_file");
            exit(0);
        }

		total_time = 0;
		peak_time = 0;

        break;

    case START:

		start_time = get_time();

        break;

    case STOP:

		end_time = get_time();

		delta = end_time - start_time;

		total_time += delta;
		if(delta > peak_time) peak_time = delta;

        fprintf(profile_file, "Time taken: %d microsec\n", (int)delta);
		frame_count++;

        break;

    case CLOSE:

    	fprintf(profile_file, "============================================\n");

    	fprintf(profile_file, "NOTE: Please confirm that your board is really configured at the frequency as mentioned below !!\n");

        fprintf(profile_file, "Peak time taken: %d microsec\n", (int)peak_time);
        fprintf(profile_file, "Avg time taken: %d microsec\n\n", (int)(total_time/frame_count));

		fprintf(profile_file, "Assuming ARM clock frequency of %d MHz for DM6446\n", ARM_CLOCK_DM6446);
		fprintf(profile_file, "Peak MCPS (for 100 calls/sec): %3.2f\n",(peak_time * ARM_CLOCK_DM6446)/10000);
		fprintf(profile_file, "Avg MCPS (for 100 calls/sec): %3.2f\n\n",((total_time/frame_count) * ARM_CLOCK_DM6446)/10000);

		fprintf(profile_file, "Assuming DSP clock frequency of %d MHz for DM6446\n", DSP_CLOCK_DM6446);
		fprintf(profile_file, "Peak MCPS (for 100 calls/sec): %3.2f\n",(peak_time * DSP_CLOCK_DM6446)/10000);
	    fprintf(profile_file, "Avg MCPS (for 100 calls/sec): %3.2f\n\n",((total_time/frame_count) * DSP_CLOCK_DM6446)/10000);

		fprintf(profile_file, "Assuming ARM clock frequency of %d MHz for DM355\n", ARM_CLOCK_DM355);
		fprintf(profile_file, "Peak MCPS (for 100 calls/sec): %3.2f\n",(peak_time * ARM_CLOCK_DM355)/10000);
		fprintf(profile_file, "Avg MCPS (for 100 calls/sec): %3.2f\n\n",((total_time/frame_count) * ARM_CLOCK_DM355)/10000);

        fclose(profile_file);

        break;

    default:
        printf("\nNot a valid command for profile_algorithm");
        exit(0);
    }
}

/*****************************************************************************/
/*                                                                           */
/*  Function Name : cache_algorithm() 	                                 	 */
/*                                                                           */
/*  Description   : This function is just dummy here. Supposed to be         */
/*					writeback/flushing cache otherwise			 		     */
/*                                                                           */
/*  Inputs        : None				         							 */
/*  Globals       : No global variables being used                           */
/*  Processing    : None							                         */
/*  Outputs       : None                                                     */
/*  Returns       : None  			                         			     */
/*  Issues        : None                                                     */
/*                                                                           */
/*  Revision History:                                                        */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*         09 01 2008   Ittiam          First draft                          */
/*                                                                           */
/*****************************************************************************/

void cache_algorithm(COMMAND cmd)
{
    return;
}

/*****************************************************************************/
/*                                                                           */
/*  Function Name : interrupt_algorithm()                                 	 */
/*                                                                           */
/*  Description   : This function is just dummy here. Supposed to be         */
/*					enable/disable interrupts	   				 		     */
/*                                                                           */
/*  Inputs        : None				         							 */
/*  Globals       : No global variables being used                           */
/*  Processing    : None							                         */
/*  Outputs       : None                                                     */
/*  Returns       : None  			                         			     */
/*  Issues        : None                                                     */
/*                                                                           */
/*  Revision History:                                                        */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*         09 01 2008   Ittiam          First draft                          */
/*                                                                           */
/*****************************************************************************/

void interrupt_algorithm(COMMAND cmd)
{
    return;
}

/*****************************************************************************/
/*                                                                           */
/*  Function Name : algo_testing                                             */
/*                                                                           */
/*  Description   : This function is written at the top of main profile,     */
/*                  stack and interrupt testing functions. Aim is to abstract*/
/*                  those testing fucntion calls.                            */
/*  Inputs        : code for the test to be performed                        */
/*  Globals       : None. Called function interrupt() uses that.             */
/*  Processing    : Depending on the testing to be performed appropriate     */
/*                  testing functions are called.                            */
/*  Outputs       : No particular output. Performs the desired testing.      */
/*                  Generates profile values or interrupt counts etc.        */
/*  Returns       : <What does the function return?>                         */
/*                                                                           */
/*  Issues        : This function is built on top of the already written     */
/*                  functions. If freshly written, it may be more efficient. */
/*                                                                           */
/*  Revision History:                                                        */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*         10 07 2006   Kumar B         Initial version                      */
/*                                                                           */
/*****************************************************************************/

void algo_testing(int test, int command)
{
    switch(test)
    {
        case NO_TEST:
        /* Dummy function call */
        break;

        case INTERRUPT_TEST:
        interrupt_algorithm(command);
        break;

        case PROFILE_TEST:

        profile_algorithm(command);
        if(command == OPEN)
        {
           cache_algorithm(START);
        }
        else if(command == START)
        {
            cache_algorithm(FLUSH);
        }
        break;

        case STACK_TEST:
        {
			/* Not supported for ARM9E-Linux yet */
        }
        break;

        default:
        printf("Unsupported test!\n");
        break;
    }

    return;
}

/* End of file */
