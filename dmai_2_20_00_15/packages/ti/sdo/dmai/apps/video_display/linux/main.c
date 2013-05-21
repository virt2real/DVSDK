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
/*
 * dm355: Only NTSC and PAL display standards are supported.
 *
 * dm6446: Only NTSC and PAL display standards are supported.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include <xdc/std.h>

#include "../appMain.h"

/* Default arguments for app */
#define DEFAULT_ARGS { 1000, FALSE, TRUE, VideoStd_D1_NTSC, Display_Output_COMPOSITE }

/*
 * Argument IDs for long options. They must not conflict with ASCII values,
 * so start them at 256.
 */
typedef enum
{
   ArgID_DISPLAY_STANDARD = 256,
   ArgID_DISPLAY_BUFFER,
   ArgID_BENCHMARK,
   ArgID_HELP,
   ArgID_NUMFRAMES,
   ArgID_DISPLAY_OUTPUT,
   ArgID_NUMARGS
} ArgID;

/******************************************************************************
 * usage
 ******************************************************************************/
static Void usage(void)
{
    fprintf(stderr, "Usage: video_display_<platform> [options]\n\n"
     "Options:\n"
     "-y | --display_standard  Video standard to use for display (see below)\n"
     "-O | --display_output    Video output to use (see below)\n"
     "     --display_buffer    Buffer allocation type for display driver (see below)\n"
     "     --benchmark         Print benchmarking information\n"
     "-h | --help              Print usage information (this message)\n"
     "-n | --numframes         Number of frames to process [Default: 1000]\n"
     "\n"
     "Display standards available:\n"
     "\t1\tD1 NTSC @ 30 fps [Default]\n"
     "\t2\tD1 PAL @ 25 fps\n"
     "\t3\t480P @ 60 fps\n"
     "\t4\t576P @ 50 fps\n"
     "\t5\t720P @ 60 fps\n"
     "\t6\t720P @ 50 fps\n"
     "\t7\t1080i @ 30 fps\n"
     "\t8\t1080i @ 25 fps\n"
     "\t9\t1080p @ 30 fps\n"
     "\t10\t1080p @ 25 fps\n"
     "\t11\t1080p @ 24 fps\n"
     "\t12\t1080p @ 60 fps\n"
     "\t13\t1080p @ 50 fps\n"
     "\t14\tVGA\n"
     "\t15\tQVGA\n"
     "\t16\tAUTO\n\n"
     "Video output available:\n"
     "\tcomposite [Default]\n"
     "\tsvideo \n"
     "\tcomponent\n"
     "\tlcd\n"
     "\tdvi\n"
     "\tauto (select video output by reading sysfs)\n"
     "Display buffer allocation type available:\n"
     "\t1\tuser [Default]\n"
     "\t2\tmmap\n");
}


/******************************************************************************
 * parseArgs
 ******************************************************************************/
static Void parseArgs(Int argc, Char *argv[], Args *argsp)
{
    const char shortOptions[] = "y:O:b:hn:";

    const struct option longOptions[] = {
        {"display_standard", required_argument, NULL, ArgID_DISPLAY_STANDARD },
        {"display_output",   required_argument, NULL, ArgID_DISPLAY_OUTPUT   },
        {"display_buffer",   required_argument, NULL, ArgID_DISPLAY_BUFFER   },
        {"benchmark",        no_argument,       NULL, ArgID_BENCHMARK        },
        {"help",             no_argument,       NULL, ArgID_HELP             },
        {"numframes",        required_argument, NULL, ArgID_NUMFRAMES        },
        {0, 0, 0, 0}
    };

    Int index;
    Int argID;

    for (;;) {
        argID = getopt_long(argc, argv, shortOptions, longOptions, &index);

        if (argID == -1) {
            break;
        }

        switch (argID) {

            case ArgID_HELP:
            case 'h':
                usage();
                exit(EXIT_SUCCESS);

            case ArgID_NUMFRAMES:
            case 'n':
                argsp->numFrames = atoi(optarg);
                break;

            case ArgID_DISPLAY_BUFFER:
                switch (atoi(optarg)) {
                    case 1:
                        argsp->displayUalloc = TRUE;
                        break;
                    case 2:
                        argsp->displayUalloc = FALSE;
                        break;
                    default:
                        fprintf(stderr, "Unknown display allocation buffer type\n");
                        usage();
                        exit(EXIT_FAILURE);
		}
                break;

            case ArgID_DISPLAY_STANDARD:
            case 'y':
                switch (atoi(optarg)) {
                    case 1:
                        argsp->videoStd = VideoStd_D1_NTSC;
                        break;
                    case 2:
                        argsp->videoStd = VideoStd_D1_PAL;
                        break;
                    case 3:
                        argsp->videoStd = VideoStd_480P;
                        break;
                    case 4:
                        argsp->videoStd = VideoStd_576P;
                        break;
                    case 5:
                        argsp->videoStd = VideoStd_720P_60;
                        break;
                    case 6:
                        argsp->videoStd = VideoStd_720P_50;
                        break;
                    case 7:
                        argsp->videoStd = VideoStd_1080I_30;
                        break;
                    case 8:
                        argsp->videoStd = VideoStd_1080I_25;
                        break;
                    case 9:
                        argsp->videoStd = VideoStd_1080P_30;
                        break;
                    case 10:
                        argsp->videoStd = VideoStd_1080P_25;
                        break;
                    case 11:
                        argsp->videoStd = VideoStd_1080P_24;
                        break;
                    case 12:
                        argsp->videoStd = VideoStd_1080P_60;
                        break;
                    case 13:
                        argsp->videoStd = VideoStd_1080P_50;
                        break;
                    case 14:
                        argsp->videoStd = VideoStd_VGA;
                        break;
                    case 15:
                        argsp->videoStd = VideoStd_QVGA;
                        break;
                    case 16:
                        argsp->videoStd = VideoStd_AUTO;
                        break;
                    default:
                        fprintf(stderr, "Unknown display resolution\n");
                        usage();
                        exit(EXIT_FAILURE);
                }
                break;

            case ArgID_DISPLAY_OUTPUT:
            case 'O':
                if (strcmp(optarg, "composite") == 0) {
                    argsp->videoOutput = Display_Output_COMPOSITE;
                } else if (strcmp(optarg, "svideo") == 0) {
                    argsp->videoOutput = Display_Output_SVIDEO;
                } else if (strcmp(optarg, "component") == 0) {
                    argsp->videoOutput = Display_Output_COMPONENT;
                } else if (strcmp(optarg, "lcd") == 0) {
                    argsp->videoOutput = Display_Output_LCD;
                } else if (strcmp(optarg, "dvi") == 0) {
                    argsp->videoOutput = Display_Output_DVI;
                } else if (strcmp(optarg, "auto") == 0) {
                    argsp->videoOutput = Display_Output_SYSTEM;
                } else {
                    fprintf(stderr, "Unknown display output\n");
                    usage();
                    exit(EXIT_FAILURE);
                }          
                break;
    
            case ArgID_BENCHMARK:
                argsp->benchmark = TRUE;
                break;

            default:
                usage();
                exit(EXIT_FAILURE);
        }
    }

    if (optind < argc) {
        usage();
        exit(EXIT_FAILURE);
    }
}


/******************************************************************************
 * main
 ******************************************************************************/
Int main(Int argc, Char *argv[])
{
    Args args = DEFAULT_ARGS;
    Int ret;
    
    /* Parse the arguments given to the app */
    parseArgs(argc, argv, &args);    

    ret = appMain(&args);
    
    return ret;
}
