/* 
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
 * 
 */
/*
 *  ======== Processor_dsplink_linkcfg_OMAP2530.c ========
 *
 *  This is how we configure link:
 *
 *  Link 1.40 lets the user take the generated CFG_Davinci.c file, modify
 *  link params, change the name of the global link config object, include
 *  the modified source file in the user's build, and call Proc_setup() with
 *  the address of the global link config object.
 *
 *  In CE, we insulate the user from this step, by including the configuration
 *  file in the OSAL build with DSPLink settings appropriate for CE.
 *  The user only provides the DSP memory map, which CE uses to modify the
 *  link config structure at runtime, immediately before calling Proc_setup().
 *
 *  However if the user wants to change more than just the memory map,
 *  he can take this source file and add it to its build, making some changes
 *  in his .cfg as well.
 *
 *  What follows is the original contents of dsplink\config\all\CFG_Davinci.c
 *  file. We rename the global Link Config object, rename the GPP OS object,
 *  and make all objects non-constant, so that we can modify them as necessary
 *  in Processor_create() before calling Proc_setup.
 *  Lines of code we added to the original CFG_Davinci.c file are tagged with
 *  [CE]. To update this file, pick a different CFG_Davinci.c and insert
 *  the tagged lines after #includes.
 */

/* ------- original CFG_OMAP_sdp2530.c, possibly adapted for CE: --------- */

/** ===========================================================================
 *  @file   CFG_OMAP_2530.c
 *
 *  @path   $(DSPLINK)/config/all/
 *
 *  @desc   Defines the configuration information for DSP/BIOS LINK for the
 *          OMAP platform.
 *
 *  @ver    1.51.00.06
 *  ============================================================================
 *  Copyright (c) Texas Instruments Incorporated 2002-2008
 *
 *  Use of this software is controlled by the terms and conditions found in the
 *  license agreement under which this software has been supplied or provided.
 *  ============================================================================
 */


/*  ----------------------------------- DSP/BIOS LINK Headers       */
#include <dsplink.h>
#include <procdefs.h>

#define LINKCFG_config ti_sdo_ce_ipc_Processor_linkcfg          /* [CE] */
#define LINKCFG_gppOsObject ti_sdo_ce_ipc_Processor_linkcfg_OS  /* [CE] */
#undef  CONST                                                   /* [CE] */
#define CONST                                                   /* [CE] */

#if defined (__cplusplus)
EXTERN "C" {
#endif /* defined (__cplusplus) */


/** ============================================================================
 *  @name   LINKCFG_gppOsObject
 *
 *  @desc   Extern declaration for the OS-specific configuration object.
 *          NOTE: This object is defined in the GPP OS-specific configuration
 *          file CFG_<GPPOS>.c.
 *          The type of this object is also OS-specific and is defined in
 *          linkcfgdefs_os.h for each GPP OS.
 *  ============================================================================
 */
extern LINKCFG_GppOs LINKCFG_gppOsObject ;

/** ============================================================================
 *  @name   LINKCFG_gppObject
 *
 *  @desc   Configuration object for the GPP.
 *  ============================================================================
 */
STATIC CONST LINKCFG_Gpp  LINKCFG_gppObject = {
    "ARM9",                         /* NAME           : Name of the GPP */
    16,                             /* MAXMSGQS       : Maximum MSGQs that can be opened */
    16,                             /* MAXCHNLQUEUE   : Maximum Queue Length for all channels */
    (Uint32) -1,                    /* POOLTABLEID    : ID of the POOL table (-1 if not needed) */
    0,                              /* NUMPOOLS       : Number of POOLs supported */
    (LINKCFG_GppOs *)     &LINKCFG_gppOsObject    /* GPPOSOBJECT    : Pointer to GPP OS object */
} ;

/** ============================================================================
 *  @name   LINKCFG_memTables
 *
 *  @desc   Array of memory tables in the system.
 *  ============================================================================
 */
STATIC CONST LINKCFG_MemEntry * LINKCFG_memTables [] =
{
    (LINKCFG_MemEntry *)NULL   /* Memory Table 0 - filled by CE runtime code */
} ;

/** ============================================================================
 *  @name   LINKCFG_dspObject
 *
 *  @desc   configuration object for the DSP in the system.
 *  ============================================================================
 */
STATIC CONST LINKCFG_Dsp  LINKCFG_dspObject =
{
    "OMAP2530",            /* NAME           : Name of the DSP */
    DspArch_C64x,          /* ARCHITECTURE   : DSP architecture */
    "COFF",                /* LOADERNAME     : Name of the DSP executable loader */
    FALSE,                 /* AUTOSTART      : Autostart the DSP (Not supported) */
    "DEFAULT.OUT",         /* EXECUTABLE     : Executable for autostart */
    DSP_BootMode_Boot_NoPwr,/* DODSPCTRL     : Link does no power management on 2530 */
    0x83F00020,            /* RESUMEADDR     : Resume address */
    0x83F00000,            /* RESETVECTOR    : Reset Vector for the DSP */
    0x80,                  /* RESETCODESIZE  : Size of code at DSP Reset Vector */
    1,                     /* MADUSIZE       : DSP Minimum Addressable Data Unit */
    (Uint32) -1,           /* CPUFREQ        : DSP Frequency (in KHz), -1 if default setting is to be used */
    Endianism_Little,      /* ENDIAN         : DSP Endianism */
    FALSE,                 /* WORDSWAP       : Words must be swapped when writing to memory */
    0,                     /* MEMTABLEID     : ID of the memory table used */
    0,                     /* MEMENTRIES     : Number of entries in memory table - set by CE runtime code */
    0,                     /* LINKDRVID      : ID of the link driver used */
    -1,                    /* ARG1           : Bus No of PCI card */
    -1,                    /* ARG2           : Slot No of PCI card */
    0,                     /* ARG3           : Shared memory interface */
    0,                     /* ARG4           : Physical interface 1-pci 2-vlynq */
    (Uint32) -1l,          /* ARG5           : EDMA channel number, unused for OMAP */
} ;

/** ============================================================================
 *  @name   LINKCFG_ipsTable_00
 *
 *  @desc   IPS table ID 0.
 *  ============================================================================
 */
STATIC CONST LINKCFG_Ips  LINKCFG_ipsTable_00 [] =
{
    {
        "IPS",                 /* NAME           : Name of the Inter-Processor-Signaling component */
        (Uint32) 32,           /* NUMIPSEVENTS   : Number of IPS events to be supported */
        (Uint32) 0,            /* MEMENTRY       : Memory entry ID (-1 if not needed) */
        (Uint32) 26,           /* GPPINTID       : Interrupt no. to used by the IPS on GPP-side. (-1 if uni-directional to DSP) */
        (Uint32) 55,           /* DSPINTID       : Interrupt no. to used by the IPS on DSP-side. (-1 if uni-directional to GPP) */
        (Uint32) 5,            /* DSPINTVECTORID : Interrupt vector no. to used by the IPS on DSP-side. (-1 if uni-directional to GPP) */
        (Uint32) 50000000,     /* ARGUMENT1      : Poll value for which IPS waits while sending event (-1 if infinite) */
        0                      /* ARGUMENT2      : Second IPS-specific argument */
    }
} ;

/** ============================================================================
 *  @name   LINKCFG_ipsTables
 *
 *  @desc   Array of IPS tables in the system.
 *  ============================================================================
 */
STATIC CONST LINKCFG_Ips * LINKCFG_ipsTables [] =
{
    LINKCFG_ipsTable_00        /* IPS Table 0 */
} ;

/** ============================================================================
 *  @name   LINKCFG_poolTable_00
 *
 *  @desc   Pool table ID 0.
 *  ============================================================================
 */
STATIC CONST LINKCFG_Pool  LINKCFG_poolTable_00 [] =
{
    {
        "SMAPOOL",             /* NAME           : Name of the pool */
        (Uint32) 1,            /* MEMENTRY       : Memory entry ID (-1 if not needed) */
        (Uint32) 0x70000,      /* POOLSIZE       : Size of the pool (-1 if not needed) */
        (Uint32) -1,           /* IPSID          : ID of the IPS used */
        (Uint32) -1,           /* IPSEVENTNO     : IPS Event number associated with POOL */
//        4,                     /* POOLMEMENTRY   : Pool memory region section ID */
        1,                     /* POOLMEMENTRY   : Pool memory region section ID */
        0x0,                   /* ARGUMENT1      : First Pool-specific argument */
        0x0                    /* ARGUMENT2      : Second Pool-specific argument */
    }
} ;

/** ============================================================================
 *  @name   LINKCFG_poolTables
 *
 *  @desc   Array of Pool tables in the system.
 *  ============================================================================
 */
STATIC CONST LINKCFG_Pool * LINKCFG_poolTables [] =
{
    LINKCFG_poolTable_00       /* Pool Table 0 */
} ;

/** ============================================================================
 *  @name   LINKCFG_dataTable_00
 *
 *  @desc   Data driver table ID 0.
 *  ============================================================================
 */
STATIC CONST LINKCFG_DataDrv  LINKCFG_dataTable_00 [] =
{
    {
        "ZCPYDATA",            /* NAME           : Name of the data driver */
        0,                     /* BASECHANNELID  : Base channel ID for the driver */
        16,                    /* NUMCHANNELS    : Number of channels supported */
        16384,                 /* MAXBUFSIZE     : Maximum size of buffer supported (-1 if no limit) */
        (Uint32) 1,            /* MEMENTRY       : Memory entry ID (-1 if not needed) */
        0,                     /* POOLID         : Pool id for allocating buffers */
        1,                     /* QUEUELENGTH    : Queue length for the data driver */
        0,                     /* IPSID          : ID of the IPS used */
        1,                     /* IPSEVENTNO     : IPS Event number associated with data Driver */
        0x0,                   /* ARGUMENT1      : First data driver specific argument */
        0x0                    /* ARGUMENT2      : Second data driver specific argument */
    }
} ;

/** ============================================================================
 *  @name   LINKCFG_dataTables
 *
 *  @desc   Array of Data driver tables in the system.
 *  ============================================================================
 */
STATIC CONST LINKCFG_DataDrv * LINKCFG_dataTables [] =
{
    LINKCFG_dataTable_00       /* Data Table 0 */
} ;

/** ============================================================================
 *  @name   LINKCFG_mqtObjects
 *
 *  @desc   Array of Message Queue Transport objects in the system.
 *  ============================================================================
 */
STATIC CONST LINKCFG_Mqt  LINKCFG_mqtObjects [] =
{
    {
        "ZCPYMQT",             /* NAME           : Name of the Message Queue Transport */
        (Uint32) 1,            /* MEMENTRY       : Memory entry ID (-1 if not needed) */
        (Uint32) -1,           /* MAXMSGSIZE     : Maximum message size supported (-1 if no limit) */
        0,                     /* IPSID          : ID of the IPS used */
        0,                     /* IPSEVENTNO     : IPS Event number associated with MQT */
        0x0,                   /* ARGUMENT1      : First MQT-specific argument */
        0x0                    /* ARGUMENT2      : Second MQT-specific argument */
    }
} ;

/** ============================================================================
 *  @name   LINKCFG_ringIoObjects
 *
 *  @desc   Array of RINGIO objects in the system.
 *  ============================================================================
 */
STATIC CONST LINKCFG_RingIo  LINKCFG_ringIoObjects [] =
{
    {
        "RINGIOTABLE",         /* NAME           : Name of the RingIO Table */
        0,                     /* MEMENTRY       : Memory entry ID (-1 if not needed) */
        64,                    /* NUMENTRIES     : Number of RingIO entries supported */
        0,                     /* IPSID          : ID of the IPS used */
        2                      /* IPSEVENTNO     : IPS Event number associated with RingIO */
    }
} ;

/** ============================================================================
 *  @name   LINKCFG_mplistObjects
 *
 *  @desc   Array of MPLIST objects in the system.
 *  ============================================================================
 */
STATIC CONST LINKCFG_MpList  LINKCFG_mplistObjects [] =
{
    {
        "MPLISTTABLE",         /* NAME           : Name of the MpList Table */
        1,                     /* MEMENTRY       : Memory entry ID (-1 if not needed) */
        64,                    /* NUMENTRIES     : Number of MpList entries supported */
        (Uint32) -1,           /* IPSID          : ID of the IPS used */
        (Uint32) -1            /* IPSEVENTNO     : IPS Event number associated with MpList */
    }
} ;

/** ============================================================================
 *  @name   LINKCFG_mpcsObjects
 *
 *  @desc   Array of MPCS objects in the system.
 *  ============================================================================
 */
STATIC CONST LINKCFG_Mpcs  LINKCFG_mpcsObjects [] =
{
    {
        "MPCS",                /* NAME           : Name of the MPCS Table */
        1,                     /* MEMENTRY       : Memory entry ID (-1 if not needed) */
        256,                   /* NUMENTRIES     : Number of MPCS entries supported */
        (Uint32) -1,           /* IPSID          : ID of the IPS used */
        (Uint32) -1            /* IPSEVENTNO     : IPS Event number associated with MPCS */
    }
} ;

/** ============================================================================
 *  @name   LINKCFG_gppObject
 *
 *  @desc   Configuration object for the GPP.
 *  ============================================================================
 */
STATIC CONST LINKCFG_Log  LINKCFG_logObject = {
    FALSE,             /* GDMSGQPUT         : GPP->DSP MSG Transfer  - MSGQ_put call */
    FALSE,             /* GDMSGQSENDINT     : GPP->DSP MSG Transfer  - GPP sends interrupt */
    FALSE,             /* GDMSGQISR         : GPP->DSP MSG Transfer  - DSP receives interrupt */
    FALSE,             /* GDMSGQQUE         : GPP->DSP MSG Transfer  - Message queued at DSP */
    FALSE,             /* DGMSGQPUT         : DSP->GPP MSG Transfer  - MSGQ_put call */
    FALSE,             /* DGMSGQSENDINT     : DSP->GPP MSG Transfer  - DSP sends interrupt */
    FALSE,             /* DGMSGQISR         : DSP->GPP MSG Transfer  - GPP receives interrupt */
    FALSE,             /* DGMSGQQUE         : DSP->GPP MSG Transfer  - Message queued at GPP */
    FALSE,             /* GDCHNLISSUESTART  : GPP->DSP CHNL Transfer - Entering inside ISSUE call */
    FALSE,             /* GDCHNLISSUEQUE    : GPP->DSP CHNL Transfer - ISSUE: Buffer is queued in internal structure on GPP */
    FALSE,             /* GDCHNLISSUECOMPL  : GPP->DSP CHNL Transfer - ISSUE call completed */
    FALSE,             /* GDCHNLXFERSTART   : GPP->DSP CHNL Transfer - Initiating a buffer transfer by GPP */
    FALSE,             /* GDCHNLXFERPROCESS : GPP->DSP CHNL Transfer - Actual transfer of buffer is going to take place */
    FALSE,             /* GDCHNLXFERCOMPL   : GPP->DSP CHNL Transfer - Buffer transfer is complete */
    FALSE,             /* GDCHNLRECLSTART   : GPP->DSP CHNL Transfer - Entering RECLAIM call */
    FALSE,             /* GDCHNLRECLPEND    : GPP->DSP CHNL Transfer - RECLAIM: Wait on a semaphore */
    FALSE,             /* GDCHNLRECLPOST    : GPP->DSP CHNL Transfer - RECLAIM: Posting the Semaphore */
    FALSE,             /* GDCHNLRECLCOMPL   : GPP->DSP CHNL Transfer - RECLAIM call completed */
    FALSE,             /* DGCHNLISSUEQUE    : DSP->GPP CHNL Transfer - ISSUE: Buffer is queued in internal structure on DSP */
    FALSE,             /* DGCHNLXFERSTART   : DSP->GPP CHNL Transfer - Initiating a buffer transfer by DSP */
    FALSE,             /* DGCHNLXFERPROCESS : DSP->GPP CHNL Transfer - Actual transfer of buffer is going to take place */
    FALSE,             /* DGCHNLXFERCOMPL   : DSP->GPP CHNL Transfer - Buffer transfer is complete */
    FALSE,             /* DGCHNLRECLPEND    : DSP->GPP CHNL Transfer - RECLAIM: Wait on a semaphore */
    FALSE,             /* DGCHNLRECLPOST    : DSP->GPP CHNL Transfer - RECLAIM: Posting the Semaphore */
    10,                /* MSGIDRANGESTART   : MSG ID range: lower limit */
    20                 /* MSGIDRANGEEND     : MSG ID range: upper limit */
} ;

/** ============================================================================
 *  @name   LINKCFG_linkDrvObjects
 *
 *  @desc   Array of Link driver objects in the system.
 *  ============================================================================
 */
STATIC CONST LINKCFG_LinkDrv  LINKCFG_linkDrvObjects [] =
{
    {
        "SHMDRV",              /* NAME           : Name of the link driver */
        (Uint32) 10000000,     /* HSHKPOLLCOUNT  : Poll value for which handshake waits (-1 if infinite) */
        (Uint32) 1,            /* MEMENTRY       : Memory entry ID (-1 if not needed) */
        0,                     /* IPSTABLEID     : ID of the IPS table used */
        sizeof(LINKCFG_ipsTable_00)/sizeof(LINKCFG_Ips),     /* IPSENTRIES     : Number of IPS supported */
        0,                     /* POOLTABLEID    : ID of the POOL table */
        sizeof(LINKCFG_poolTable_00)/sizeof(LINKCFG_Pool),   /* NUMPOOLS       : Number of POOLs supported */
        0,                     /* DATATABLEID    : ID of the data driver table */
        sizeof(LINKCFG_dataTable_00)/sizeof(LINKCFG_DataDrv),/* NUMDATADRV     : Number of data drivers supported */
        0,                     /* MQTID          : ID of the MQT */
        0,                     /* RINGIOTABLEID  : RingIO Table Id used for this DSP */
        0,                     /* MPLISTTABLEID  : MpList Table Id used for this DSP */
        0                      /* MPCSTABLEID    : MPCS Table ID used for this DSP */
    }
} ;

/** ============================================================================
 *  @name   LINKCFG_dspConfig
 *
 *  @desc   DSP/BIOS LINK configuration structure.
 *  ============================================================================
 */
CONST LINKCFG_DspConfig  LINKCFG_dspConfig = {
    (LINKCFG_Dsp *)       &LINKCFG_dspObject,     /* DSPOBJECT      : DSP object */
    sizeof(LINKCFG_linkDrvObjects)/sizeof(LINKCFG_LinkDrv), /* NUMLINKDRVS     : Number of Link Drivers */
    (LINKCFG_LinkDrv *)   LINKCFG_linkDrvObjects, /* LINKDRVOBJECTS : Array of Link Driver objects */
    sizeof(LINKCFG_memTables)/sizeof(LINKCFG_MemEntry *),   /* NUMMEMTABLES    : Number of memory tables */
    (LINKCFG_MemEntry **) LINKCFG_memTables,      /* MEMTABLES      : Array of Memory tables */
    sizeof(LINKCFG_ipsTables)/sizeof(LINKCFG_Ips *),        /* NUMIPSTABLES    : Number of IPS tables */
    (LINKCFG_Ips **)      LINKCFG_ipsTables,      /* IPSTABLES      : Array of IPS tables */
    sizeof(LINKCFG_poolTables)/sizeof(LINKCFG_Pool *),      /* NUMPOOLTABLES   : Number of POOL tables */
    (LINKCFG_Pool **)     LINKCFG_poolTables,     /* POOLTABLES     : Array of Pool tables */
    sizeof(LINKCFG_dataTables)/sizeof(LINKCFG_DataDrv *),   /* NUMDATATABLES   : Number of data tables */
    (LINKCFG_DataDrv **)  LINKCFG_dataTables,     /* DATATABLES     : Array of data tables */
    sizeof(LINKCFG_mqtObjects)/sizeof(LINKCFG_Mqt),         /* NUMMQTS         : Number of MQTs */
    (LINKCFG_Mqt *)       LINKCFG_mqtObjects,     /* MQTOBJECTS     : Array of MQT objects */
    sizeof(LINKCFG_ringIoObjects)/sizeof(LINKCFG_RingIo),   /* NUMRINGIOTABLES : Number of RINGIO objects */
    (LINKCFG_RingIo *)    LINKCFG_ringIoObjects,  /* RINGIOOBJECTS  : Array of RINGIO objects */
    sizeof(LINKCFG_mplistObjects)/sizeof(LINKCFG_MpList),   /* NUMMPLISTTABLES : Number of MPLIST tables */
    (LINKCFG_MpList *)    LINKCFG_mplistObjects,  /* MPLISTOBJECTS  : Array of MPLIST objects */
    sizeof(LINKCFG_mpcsObjects)/sizeof(LINKCFG_Mpcs),         /* NUMMPCSTABLES : Number of MPCS tables */
    (LINKCFG_Mpcs *)      LINKCFG_mpcsObjects,    /* MPCSOBJECTS    : Array of MPCS objects */
    (LINKCFG_Log *)       &LINKCFG_logObject      /* LOGOBJECT      : Pointer to LOG object */
} ;

/** ============================================================================
 *  @name   LINKCFG_config
 *
 *  @desc   DSP/BIOS LINK configuration structure.
 *  ============================================================================
 */
CONST LINKCFG_Object  LINKCFG_config = {
    (LINKCFG_Gpp *)       &LINKCFG_gppObject,     /* GPPOBJECT      : GPP object */
    {
        (LINKCFG_DspConfig *) &LINKCFG_dspConfig
    },
};


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
/*
 *  @(#) ti.sdo.ce.ipc.dsplink; 1, 0, 0, 0,2; 1-31-2008 19:08:42; /db/atree/library/trees/ce-i04x/src/
 */

/*
 *  @(#) ti.sdo.ce.ipc.dsplink; 2, 0, 1,182; 12-2-2010 21:24:23; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

