/*****************************************************************************/
/*                                                                           */
/*                   ITTIAM SYSTEMS PVT LTD, BANGALORE                       */
/*                          COPYRIGHT(C) 2007                                */
/*                                                                           */
/*  This program is proprietary to Ittiam Systems Pvt. Ltd. and is protected */
/*  under Indian Copyright Act as an unpublished work.Its use and disclosure */
/*  is  limited by  the terms and conditions of a license  agreement. It may */
/*  be copied or  otherwise reproduced or  disclosed  to persons outside the */
/*  licensee 's  organization  except  in  accordance  with  the  terms  and */
/*  conditions of  such an agreement. All  copies and reproductions shall be */
/*  the  property  of Ittiam Systems Pvt.  Ltd. and  must  bear  this notice */
/*  in its entirety.                                                         */
/*                                                                           */
/*****************************************************************************/

/*
 *  ======== ceapp.c ========
 *  The CodecEngine-using part of the Linux application, separated from the
 *  rest of the Linux app to simplify the interface towards the rest of
 *  the main app. CodecEngine API and especially APIs for individual codecs
 *  are much more capable than what we need for simple (dummy) audio
 *  encode/decode.
 */
/* include various CodecEngine header files */
#include <xdc/std.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/speech1/sphenc1.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/CERuntime.h>
#include <ti/xdais/dm/ispeech1_pcm.h>

#include <ti/sdo/ce/trace/gt.h>

/* define names of codecs to use */
static String encoderName  = "g711_enc";
static String engineName   = "g711_enc_engine";

/*  define handles to the CodecEngine and codecs to be used across ceapp_*
 *  function calls; we are not reentrant.
 */
Engine_Handle ceHandle  = NULL;
SPHENC1_Handle encHandle = NULL;

/*
 *  ======== traceDump ========
 *  dump contents of DSP trace -- this is a "pull" trace dumping: we read
 *  DSP's trace log whenever we think there might be something there.
 */
static void traceDump(Engine_Handle ceHandle)
{
    GT_disable(); /* temporarily disable tracing for this thread */
    Engine_fwriteTrace(ceHandle, "[DSP] ", stdout);
    GT_enable();
}

/*
 *  ======== ceapp_init ========
 */
int ceapp_init(void *params)
{
    int status = -1;    /* nonzero means failure */

    /* initialize Codec Engine runtime first */
    /* This function has been moved to main() in main.c */
    //CERuntime_init();

    /* reset, load, and start DSP Engine */
    if ((ceHandle = Engine_open(engineName, NULL, NULL)) == NULL) {
        printf("CEapp-> ERROR: can't open engine %s\n", engineName);
        goto init_end;
    }
    else
    {
        printf("CEapp-> Engine Opened: %s\n", engineName);
    }

    /*  dump contents of DSP trace -- this is a "pull" trace dumping: we read
     *  DSP's trace log whenever we think there might be something there.
     */
    traceDump(ceHandle);

    /* allocate and initialize audio encoder on the engine */
    encHandle = SPHENC1_create(ceHandle, encoderName, params);
    if (encHandle == NULL) {
        printf("CEapp-> ERROR: can't open codec %s\n", encoderName);
        goto init_end;
    }
    else
    {
        printf("CEapp-> Codec opened %s\n", encoderName);
    }
    traceDump(ceHandle);

    status = 0;     /* success */

init_end:

    return status;
}


/*
 *  ======== ceapp_allocContigBuf ========
 */
char *ceapp_allocContigBuf(int bufSize, char *description)
{
    char *buf;

    printf("CEapp-> Allocating contiguous buffer for '%s' of size %d...\n",
            description, bufSize);

    buf = (char *)Memory_contigAlloc(bufSize, Memory_DEFAULTALIGNMENT);

    if (buf == NULL) {
        printf("CEapp-> ERROR: Failed to allocate contiguous memory block.\n");
    }
    else {
        printf("CEapp-> Contiguous buffer allocated OK (phys. addr=0x%x)\n",
            (int)Memory_getBufferPhysicalAddress(buf, bufSize, NULL));
    }
    return buf;
}

/*
 *  ======== ceapp_freeContigBuf ========
 */
void ceapp_freeContigBuf(char *buf, int bufSize)
{
    Memory_contigFree(buf, bufSize);
}


/*
 *  ======== ceapp_exit ========
 */
void ceapp_exit()
{
    /* teardown the codecs and the engine */
    if (encHandle != NULL) {
        SPHENC1_delete(encHandle);
        traceDump(ceHandle);
    }
    if (ceHandle != NULL) {
        Engine_close(ceHandle);
    }
}

