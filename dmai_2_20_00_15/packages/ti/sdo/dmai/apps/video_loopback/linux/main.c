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
 * dm355:  This sample application is not supported on DM355, as it requires
 *         driver support for user-allocated buffers.
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/BufTab.h>
#include <ti/sdo/dmai/Display.h>
#include <ti/sdo/dmai/Capture.h>
#include <ti/sdo/dmai/BufferGfx.h>

#include "../appMain.h"

/* Default arguments for app */
#define DEFAULT_ARGS { 0, FALSE, Display_Output_COMPOSITE, Capture_Input_COMPOSITE, VideoStd_AUTO }

/*
 * Argument IDs for long options. They must not conflict with ASCII values,
 * so start them at 256.
 */
typedef enum
{
   ArgID_BENCHMARK = 256,
   ArgID_HELP,
   ArgID_NUMFRAMES,
   ArgID_DISPLAY_OUTPUT,
   ArgID_CAPTURE_INPUT,
   ArgID_VIDEOSTD,
   ArgID_NUMARGS
} ArgID;

/******************************************************************************
 * usage
 ******************************************************************************/
static Void usage(void)
{
    fprintf(stderr, "Usage: video_loopback_<platform> [options]\n\n"
     "Options:\n"
     "-O | --display_output    Video output to use (see below)\n"
     "     --benchmark         Print benchmarking information\n"
     "-I | --capture_input     Capture input to use (see below)\n"
     "-y | --video_standard    Video standard (see below)\n"
     "-h | --help              Print usage information (this message)\n"
     "-n | --numframes         Number of frames to process [Default: 1000]\n"
     "\n"
     "Video input available:\n"
     "\tcomposite [Default]\n"
     "\ts-video\n"
     "\tcomponent\n"
     "\tcamera\n"
     "Video output available:\n"
     "\tcomposite [Default]\n"
     "\tcomponent\n"
     "\tsvideo \n"
     "\tlcd\n"
     "\tdvi\n"
     "\tauto (select video output by reading sysfs)\n"
     "Available video standard:\n"
     "1. D1 NTSC\n"
     "2. D1 PAL\n"
     "3. 480P \n"
     "4. 720P \n"
     "5. 1080P \n"
     "6. auto (select by probing camera) [Default]\n"
     );
}

/******************************************************************************
 * parseArgs
 ******************************************************************************/
static Void parseArgs(Int argc, Char *argv[], Args *argsp)
{
    const char shortOptions[] = "O:I:hn:y:";

    const struct option longOptions[] = {
        {"display_output",   required_argument, NULL, ArgID_DISPLAY_OUTPUT   },
        {"capture_input",    no_argument,       NULL, ArgID_CAPTURE_INPUT    },
        {"benchmark",        no_argument,       NULL, ArgID_BENCHMARK        },
        {"video_standard",   required_argument, NULL, ArgID_VIDEOSTD         },
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
            case ArgID_NUMFRAMES:
            case 'n':
                argsp->numFrames = atoi(optarg);
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

            case ArgID_VIDEOSTD:
            case 'y':
                switch(atoi(optarg)) {
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
                        argsp->videoStd = VideoStd_720P_60;
                        break;
                    case 5:
                        argsp->videoStd = VideoStd_1080P_30;
                        break;
                    default:
                        argsp->videoStd = VideoStd_AUTO;
                }
                break;

            case ArgID_CAPTURE_INPUT:
            case 'I':
                if (strcmp(optarg, "composite") == 0) {
                    argsp->videoInput = Capture_Input_COMPOSITE;
                } else if (strcmp(optarg, "s-video") == 0) {
                    argsp->videoInput = Capture_Input_SVIDEO;
                } else if (strcmp(optarg, "component") == 0) {
                    argsp->videoInput = Capture_Input_COMPONENT;
                } else if (strcmp(optarg, "camera") == 0) {
                    argsp->videoInput = Capture_Input_CAMERA;
                } else {
                    fprintf(stderr, "Unknown display output\n");
                    usage();
                    exit(EXIT_FAILURE);
                }          
                break;

            case ArgID_HELP:
            case 'h':
                usage();
                exit(EXIT_SUCCESS);

            default:
                usage();
                exit(EXIT_FAILURE);
        }

    }

    if ((argsp->videoInput == Capture_Input_COMPONENT) && 
       (argsp->videoStd == VideoStd_1080P_30)) {
        argsp->videoStd = VideoStd_1080I_60;
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
