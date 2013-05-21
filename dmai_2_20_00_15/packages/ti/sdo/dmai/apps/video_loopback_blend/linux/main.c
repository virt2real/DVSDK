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
 * dm6467: The width of --position, --input_position and -r need to be even.
 *         If --in_place is used, --bitmap_position needs to be a multiple of 8.
 *         Due to 2 bpp bitmap and the constraint that the bmp pitch needs to
 *         be a multiple of 8, the width of --bitmap_resolution need to be a
 *         multiple of 32. Example usage:
 *
 *         ./video_loopback_blend_dm6467.x470MV --bitmap_position 147x157 \
 *              --bitmap_resolution 160x159 --r 632x479 \
 *              --input_position 320x229 --position 128x67
 *
 *         ./video_loopback_blend_dm6467.x470MV --bitmap_position 144x157 \
 *              --bitmap_resolution 160x159 --r 632x479 \
 *              --input_position 320x229 --position 128x67 --in_place
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>

#include <xdc/std.h>

#include "../appMain.h"

/* Default arguments for app */
#define DEFAULT_ARGS { 0, FALSE, FALSE, 0, 0, 0, 0, 0, 0, -1, -1, 320, 320, FALSE, FALSE, Display_Output_COMPOSITE }

/*
 * Argument IDs for long options. They must not conflict with ASCII values,
 * so start them at 256.
 */
typedef enum
{
   ArgID_BENCHMARK = 256,
   ArgID_CAPTURE_UALLOC,
   ArgID_DISPLAY_UALLOC,
   ArgID_FCOPY_ACCEL,
   ArgID_POSITION,
   ArgID_INPUT_POSITION,
   ArgID_RESOLUTION,
   ArgID_HELP,
   ArgID_IN_PLACE,
   ArgID_NUMFRAMES,
   ArgID_BITMAP_POSITION,
   ArgID_BITMAP_RESOLUTION,
   ArgID_DISPLAY_OUTPUT,
   ArgID_NUMARGS
} ArgID;

/******************************************************************************
 * usage
 ******************************************************************************/
static Void usage(void)
{
    fprintf(stderr, "Usage: video_loopback_blend_<platform> [options]\n\n"
        "Options:\n"
        "-O | --display_output    Video output to use (see below)\n"
        "     --benchmark         Print benchmarking information\n"
        "     --capture_ualloc    User allocates buffers for capture driver\n"
        "     --display_ualloc    User allocates buffers for display driver\n"
        "     --in_place          Use the same buffer as source and\n"
        "                         destination when blending\n"
        "     --position          Output position ('x-offset'x'y-offset')\n"
        "                         position origin [Default: 0x0] is the\n"
        "                         upper-left corner of the screen\n"
        "                         Only used with --resolution.\n"
        "-r | --resolution        Image resolution ('width'x'height')\n"
        "                         [Defaults to same as display standard]\n"
        "     --input_position    Input position ('x-offset'x'y-offset')\n"
        "                         position origin [Default: 0x0] is the\n"
        "                         upper-left corner of the screen.\n"
        "                         Only used with --input_resolution.\n"
        "     --bitmap_position   Bitmap position ('x-offset'x'y-offset') "
                                  "[0x0];\n"
        "                         position origin (0x0) is the upper-left\n"
        "                         corner of the screen.\n"
        "     --bitmap_resolution Bitmap resolution ('width'x'height') "
                                  "[320x320]\n"
        "-h | --help              Print usage information (this message)\n"
        "-n | --numframes         Number of frames to process [Default: 0 "
                                  "(infinite)]\n"
        "\nVideo output available:\n"
        "\tcomposite [Default]\n"
        "\tsvideo \n"
        "\tcomponent\n"
        "\tauto (select video output by reading sysfs)\n");
}

/******************************************************************************
 * parseArgs
 ******************************************************************************/
static Void parseArgs(Int argc, Char *argv[], Args *argsp)
{
    const char shortOptions[] = "O:hn:r:";

    const struct option longOptions[] = {
      {"benchmark",          no_argument,       NULL, ArgID_BENCHMARK         },
      {"display_output",     required_argument, NULL, ArgID_DISPLAY_OUTPUT    },
      {"capture_ualloc",     no_argument,       NULL, ArgID_CAPTURE_UALLOC    },
      {"display_ualloc",     no_argument,       NULL, ArgID_DISPLAY_UALLOC    },
      {"in_place",           no_argument,       NULL, ArgID_IN_PLACE          },
      {"position",           required_argument, NULL, ArgID_POSITION          },
      {"resolution",         required_argument, NULL, ArgID_RESOLUTION        },
      {"input_position",     required_argument, NULL, ArgID_INPUT_POSITION    },
      {"bitmap_position",    required_argument, NULL, ArgID_BITMAP_POSITION   },
      {"bitmap_resolution",  required_argument, NULL, ArgID_BITMAP_RESOLUTION },
      {"numframes",          required_argument, NULL, ArgID_NUMFRAMES         },
      {"help",               no_argument,       NULL, ArgID_HELP              },
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

            case ArgID_DISPLAY_OUTPUT:
            case 'O':
                if (strcmp(optarg, "composite") == 0) {
                    argsp->videoOutput = Display_Output_COMPOSITE;
                } else if (strcmp(optarg, "svideo") == 0) {
                    argsp->videoOutput = Display_Output_SVIDEO;
                } else if (strcmp(optarg, "component") == 0) {
                    argsp->videoOutput = Display_Output_COMPONENT;
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

            case ArgID_HELP:
            case 'h':
                usage();
                exit(EXIT_SUCCESS);

            case ArgID_IN_PLACE:
                argsp->inplace = TRUE;
                break;

            case ArgID_NUMFRAMES:
            case 'n':
                argsp->numFrames = atoi(optarg);
                break;

            case ArgID_POSITION:
                if (sscanf(optarg, "%dx%d", &argsp->xOut,
                                            &argsp->yOut) != 2) {
                    fprintf(stderr, "Invalid position supplied (%s)\n",
                            optarg);
                    usage();
                    exit(EXIT_FAILURE);
                }
                break;

            case ArgID_INPUT_POSITION:
                if (sscanf(optarg, "%dx%d", &argsp->xIn,
                                            &argsp->yIn) != 2) {
                    fprintf(stderr, "Invalid position supplied (%s)\n",
                            optarg);
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

            case ArgID_RESOLUTION:
            case 'r':
                if (sscanf(optarg, "%dx%d", &argsp->width,
                                            &argsp->height) != 2) {
                    fprintf(stderr, "Invalid resolution supplied (%s)\n",
                            optarg);
                    usage();
                    exit(EXIT_FAILURE);
                }
                break;

            case ArgID_BITMAP_RESOLUTION:
                if (sscanf(optarg, "%dx%d", &argsp->bitmapWidth,
                                            &argsp->bitmapHeight) != 2) {
                    fprintf(stderr, "Invalid resolution supplied (%s)\n",
                            optarg);
                    usage();
                    exit(EXIT_FAILURE);
                }
                break;

            case ArgID_BITMAP_POSITION:
                if (sscanf(optarg, "%dx%d", &argsp->xBitmap,
                                            &argsp->yBitmap) != 2) {
                    fprintf(stderr, "Invalid bitmap position supplied (%s)\n",
                            optarg);
                    usage();
                    exit(EXIT_FAILURE);
                }
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
    
    /* Parse the arguments given to the app */
    parseArgs(argc, argv, &args);    

    appMain(&args);
    
    return 0;
}
