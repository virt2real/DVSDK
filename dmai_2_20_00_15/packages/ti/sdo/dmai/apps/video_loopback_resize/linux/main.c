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
 * dm6467: When --input_resolution and -r are used, the width need to be even.
 *         When --position and --input_position are used, the x value needs
 *         to be a multiple of 8. --crop is not supported due to H/W limitation.
 *         Only downsampling is supported. Example usage:
 *
 *         ./video_loopback_resize_dm6467.x470MV --position 112x128 -y 5 \
 *             --input_position 128x128 --input_resolution 121x120 -r 402x350
 *
 * dm6446: --capture_ualloc and display_ualloc is not supported due to device
 *         driver limitation. Only NTSC and PAL are supported with the -y
 *         parameter. When doing vertical upsampling the width of -r must be a
 *         multiple of 8, otherwise it needs to be even. The width of
 *         --input_position and --position needs to be a multiple of 16.
 *         Example usage:
 *
 *         ./video_loopback_resize_dm6446.x470MV -r 368x343 --input_resolution \
 *             319x239 --position 96x89 --input_position 160x33
 *
 *         ./video_loopback_resize_dm6446.x470MV -r 324x239 --input_resolution \
 *             455x343 --position 96x89 --input_position 160x33
 *
 * dm355:  --capture_ualloc and display_ualloc is not supported due to device
 *         driver limitation. Only NTSC and PAL are supported with the -y
 *         parameter. 
 *
 *         All IPIPE hardware restrictions apply, and the application will fail
 *         if any property is violated.  
 *
 *         The main thing to be aware of is that buffer accesses must start
 *         on 32-byte boundaries.  For the most part, this means your
 *         horizontal argument to --position must be a multiple of 16.
 *         Example usage:
 *
 *         ./video_loopback_resize_dm355.x470MV -r 368x343 --input_resolution \
 *             319x239 --position 96x89 --input_position 160x33
 *
 *         ./video_loopback_resize_dm355.x470MV -r 324x239 --input_resolution \
 *             455x343 --position 96x89 --input_position 160x33
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>

#include <xdc/std.h>

#include <ti/sdo/dmai/VideoStd.h>

#include "../appMain.h"

/* Default arguments for app */
#define DEFAULT_ARGS { VideoStd_D1_NTSC, 0, FALSE, FALSE, FALSE, FALSE, 0, 0, \
    0, 0, -1, -1, -1, -1 , Display_Output_COMPOSITE, Capture_Input_COMPOSITE}

/*
 * Argument IDs for long options. They must not conflict with ASCII values,
 * so start them at 256.
 */
typedef enum
{
   ArgID_BENCHMARK = 256,
   ArgID_DISPLAY_STANDARD,
   ArgID_CAPTURE_UALLOC,
   ArgID_DISPLAY_UALLOC,
   ArgID_POSITION,
   ArgID_INPUT_POSITION,
   ArgID_RESOLUTION,
   ArgID_INPUT_RESOLUTION,
   ArgID_CROP,
   ArgID_HELP,
   ArgID_NUMFRAMES,
   ArgID_DISPLAY_OUTPUT,
   ArgID_CAPTURE_INPUT,
   ArgID_NUMARGS
} ArgID;


/******************************************************************************
 * usage
 ******************************************************************************/
static Void usage(void)
{
    fprintf(stderr, "Usage: video_loopback_resize_<platform> [options]\n\n"
        "Options:\n"
        "     --benchmark         Print benchmarking information\n"
        "-y | --display_standard  Video std to use for display (see below)\n"
        "-O | --display_output    Video output to use (see below)\n"
        "-I | --capture_input     Video input to use (see below)\n"
        "     --capture_ualloc    User allocates buffers for capture driver\n"
        "     --display_ualloc    User allocates buffers for display driver\n"
        "     --position          Output position ('x-offset'x'y-offset')\n"
        "                         position origin [Default: 0x0] is the\n"
        "                         upper-left corner of the screen\n"
        "                         Only used with --resolution.\n"
        "-r | --resolution        Output resolution ('width'x'height')\n"
        "                         [Defaults to same as display standard]\n"
        "     --input_position    Input position ('x-offset'x'y-offset')\n"
        "                         position origin [Default: 0x0] is the\n"
        "                         upper-left corner of the screen.\n"
        "                         Only used with --input_resolution.\n"
        "     --input_resolution  Input resolution ('width'x'height')\n"
        "                         [Defaults to same as capture standard]\n"
        "     --crop              If --input_resolution is set, use cropping\n"
        "                         on the video input to set this resolution.\n"
        "                         (crop not supported for DM6467)\n"
        "-h | --help              Print usage information (this message)\n"
        "-n | --numframes         Number of frames to process [Default: 0 "
                                  "(infinite)]\n"
        "\n"
        "Display standards available:\n"
        "\t1\tD1 @ 30 fps (NTSC) [Default]\n"
        "\t2\tD1 @ 25 fps (PAL)\n"
        "\t3\t480P @ 60 fps\n"
        "\t4\t576P @ 50 fps\n"
        "\t5\t720P @ 60 fps\n"
        "\t6\t720P @ 50 fps\n"
        "\t7\t1080i @ 30 fps\n"
        "\t8\t1080i @ 25 fps\n\n"
        "Video outputs available:\n"
        "\tcomposite [Default]\n"
        "\tsvideo \n"
        "\tcomponent\n"
        "\tlcd\n"
        "\tdvi\n"
        "\tauto (select video output by reading sysfs)\n\n"
        "Video inputs available:\n"
        "\tcomposite [Default]\n"
        "\ts-video\n"
        "\tcomponent\n");
}

/******************************************************************************
 * parseArgs
 ******************************************************************************/
static Void parseArgs(Int argc, Char *argv[], Args *argsp)
{
    const char shortOptions[] = "y:r:O:I:hn:";

    const struct option longOptions[] = {
        {"benchmark",        no_argument,       NULL, ArgID_BENCHMARK        },
        {"display_standard", required_argument, NULL, ArgID_DISPLAY_STANDARD },
        {"display_output",   required_argument, NULL, ArgID_DISPLAY_OUTPUT   },
        {"capture_input",    required_argument, NULL, ArgID_CAPTURE_INPUT    },
        {"capture_ualloc",   no_argument,       NULL, ArgID_CAPTURE_UALLOC   },
        {"display_ualloc",   no_argument,       NULL, ArgID_DISPLAY_UALLOC   },
        {"position",         required_argument, NULL, ArgID_POSITION         },
        {"resolution",       required_argument, NULL, ArgID_RESOLUTION       },
        {"input_position",   required_argument, NULL, ArgID_INPUT_POSITION   },
        {"input_resolution", required_argument, NULL, ArgID_INPUT_RESOLUTION },
        {"crop",             no_argument,       NULL, ArgID_CROP             },
        {"help",             no_argument,       NULL, ArgID_HELP             },
        {"numframes",        required_argument, NULL, ArgID_NUMFRAMES        },
        {0, 0, 0, 0}
    };

    Int  index;
    Int  argID;

    for (;;) {
        argID = getopt_long(argc, argv, shortOptions, longOptions, &index);

        if (argID == -1) {
            break;
        }

        switch (argID) {

            case ArgID_BENCHMARK:
                argsp->benchmark = TRUE;
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
                    default:
                        fprintf(stderr, "Unknown display resolution\n");
                        usage();
                        exit(EXIT_FAILURE);
                }
                break;

            case ArgID_CAPTURE_INPUT:
            case 'I':
                if (strcmp(optarg, "composite") == 0) {
                    argsp->videoInput = Capture_Input_COMPOSITE;
                } else if (strcmp(optarg, "svideo") == 0) {
                    argsp->videoInput = Capture_Input_SVIDEO;
                } else if (strcmp(optarg, "component") == 0) {
                    argsp->videoInput = Capture_Input_COMPONENT;
                } else {
                    fprintf(stderr, "Unknown capture input\n");
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
    
            case ArgID_CAPTURE_UALLOC:
                argsp->captureUalloc = TRUE;
                break;

            case ArgID_DISPLAY_UALLOC:
                argsp->displayUalloc = TRUE;
                break;

            case ArgID_POSITION:
                if (sscanf(optarg, "%ldx%ld", &argsp->xOut,
                                              &argsp->yOut) != 2) {
                    fprintf(stderr, "Invalid position supplied (%s)\n",
                            optarg);
                    usage();
                    exit(EXIT_FAILURE);
                }
                break;

            case ArgID_INPUT_POSITION:
                if (sscanf(optarg, "%ldx%ld", &argsp->xIn,
                                              &argsp->yIn) != 2) {
                    fprintf(stderr, "Invalid position supplied (%s)\n",
                            optarg);
                    usage();
                    exit(EXIT_FAILURE);
                }
                break;

            case ArgID_RESOLUTION:
            case 'r':
                if (sscanf(optarg, "%ldx%ld", &argsp->outWidth,
                                              &argsp->outHeight) != 2) {
                    fprintf(stderr, "Invalid resolution supplied (%s)\n",
                            optarg);
                    usage();
                    exit(EXIT_FAILURE);
                }
                break;

            case ArgID_INPUT_RESOLUTION:
                if (sscanf(optarg, "%ldx%ld", &argsp->inWidth,
                                              &argsp->inHeight) != 2) {
                    fprintf(stderr, "Invalid resolution supplied (%s)\n",
                            optarg);
                    usage();
                    exit(EXIT_FAILURE);
                }
                break;

            case ArgID_CROP:
                argsp->crop = TRUE;
                break;

            case ArgID_HELP:
            case 'h':
                usage();
                exit(EXIT_SUCCESS);

            case ArgID_NUMFRAMES:
            case 'n':
                argsp->numFrames = atoi(optarg);
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
