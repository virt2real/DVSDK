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
/** ============================================================================
 *  @file   gpptypes.h
 *
 *  @path   $(DSPLINK)\gpp\inc
 *
 *  @desc   Defines the type system for DSP/BIOS Link
 *
 *  @ver    01.30.04
 *  ============================================================================
 *  Copyright (c) Texas Instruments Incorporated 2002-2005
 *
 *  Use of this software is controlled by the terms and conditions found in the
 *  license agreement under which this software has been supplied or provided.
 *  ============================================================================
 */


#if !defined (GPPTYPES_H)
#define GPPTYPES_H


#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */


/** ============================================================================
 *  @macro  IN/OUT/OPTIONAL/CONST
 *
 *  @desc   Argument specification syntax
 *  ============================================================================
 */
#define IN                              /* The argument is INPUT  only */
#define OUT                             /* The argument is OUTPUT only */
#define OPT                             /* The argument is OPTIONAL    */
#define CONST   const

/** ============================================================================
 *  @macro  USES
 *
 *  @desc   Empty macro to indicate header file dependency
 *  ============================================================================
 */
#define USES(filename)


/** ============================================================================
 *  @macro  Data types
 *
 *  @desc   Basic data types
 *  ============================================================================
 */
#if 0 /* [CE] disabled these typedefs as they conflict XDC's */ 
typedef signed char         Int8 ;      /*  8 bit value */
typedef signed short int    Int16 ;     /* 16 bit value */
typedef signed long  int    Int32 ;     /* 32 bit value */

typedef unsigned char       Uint8 ;     /*  8 bit value */
typedef unsigned short int  UInt16 ;    /* 16 bit value */
typedef unsigned long  int  UInt32 ;    /* 32 bit value */
#endif

typedef float               Real32 ;    /* 32 bit value */
typedef double              Real64 ;    /* 64 bit value */

#if 0 /* [CE] disabled these typedefs as they conflict XDC's */ 
typedef short int           Bool ;      /* 16 bit value */
#endif

typedef char                Char8 ;     /*  8 bit value */
typedef short               Char16 ;    /* 16 bit value */

typedef unsigned char       Uchar8 ;    /*  8 bit value */
typedef unsigned short      Uchar16 ;   /* 16 bit value */

/* TBD resolve this with hal_psc.c */
#if 0 /* [CE] disabled these typedefs as they conflict XDC's */ 
typedef int                 Int ;

#define Void                void
#endif
typedef void *              Pvoid ;

typedef Char8 *             Pstr ;
typedef Uchar8 *            Pustr ;


/** ============================================================================
 *  @const  TRUE/FALSE
 *
 *  @desc   Boolean constants
 *  ============================================================================
 */
#if !defined (FALSE)
#define FALSE   0
#endif

#if !defined (TRUE)
#define TRUE    1
#endif


/** ============================================================================
 *  @const  NULL
 *
 *  @desc   Definition is language specific
 *  ============================================================================
 */
#if !defined (NULL)

#if defined (__cplusplus)
#define NULL    0
#else  /* defined (__cplusplus) */
#define NULL ((void *)0)
#endif /* defined (__cplusplus) */

#endif /* !defined (NULL) */


/** ============================================================================
 *  @const  NULL_CHAR
 *
 *  @desc   String terminator.
 *  ============================================================================
 */
#define NULL_CHAR '\0'


/** ============================================================================
 *  @macro  REG8/REG16/REG32
 *
 *  @desc   Macros to access register fields.
 *  ============================================================================
 */
#define REG8(A)         (*(volatile Char8  *) (A))
#define REG16(A)        (*(volatile UInt16 *) (A))
#define REG32(A)        (*(volatile UInt32 *) (A))


/** ============================================================================
 *  @macro  DSP/BIOS Link specific types
 *
 *  @desc   These types are used across DSP/BIOS Link.
 *  ============================================================================
 */
typedef UInt32     ProcessorId ;
typedef UInt32     ChannelId ;
typedef UInt32     LinkId ;


/** ============================================================================
 *  @name   PoolId
 *
 *  @desc   This type is used for identifying the different pools used by
 *          DSPLINK.
 *  ============================================================================
 */
typedef UInt16     PoolId ;


/** ============================================================================
 *  @macro  OS Specific standard definitions
 *
 *  @desc   Free for OEMs to add their own generic stuff, if they so desire
 *  ============================================================================
 */
#if defined (OS_WINCE)

#endif  /* defined (OS_WINCE) */


#if defined (OS_NUCLEUS)

#endif  /* defined (OS_NUCLEUS) */


#if defined (OS_LINUX)

#endif  /* defined (OS_LINUX) */


/** ============================================================================
 *  @macro  Calling convention
 *
 *  @desc   Definition of CDECL, DLLIMPORT, DLLEXPORT can be defined by
 *          OEM for his compiler
 *  ============================================================================
 */
#define STATIC          static
#define EXTERN          extern


#if defined (OS_WINCE)
/*  ------------------------------------------- WINCE               */
#define CDECL           __cdecl
#define DLLIMPORT       __declspec (dllexport)
#define DLLEXPORT       __declspec (dllexport)
/*  ------------------------------------------- WINCE               */
#endif  /* defined (OS_WINCE) */


#if defined (OS_NUCLEUS)
/*  ------------------------------------------- NUCLEUS             */
#define CDECL
#define DLLIMPORT
#define DLLEXPORT
/*  ------------------------------------------- NUCLEUS             */
#endif  /* defined (OS_NUCLEUS) */

#if defined (OS_LINUX)
/*  ------------------------------------------- LINUX               */
#define CDECL
#define DLLIMPORT
#define DLLEXPORT
/*  ------------------------------------------- LINUX               */
#endif  /* defined (OS_LINUX) */


#if defined (OS_PROS)
/*  ------------------------------------------- PROS                */
#define CDECL
#define DLLIMPORT
#define DLLEXPORT
/*  ------------------------------------------- PROS                */
#endif  /* defined (OS_PROS) */

/* Derived calling conventions */
#define NORMAL_API      CDECL
#define IMPORT_API      DLLIMPORT
#define EXPORT_API      DLLEXPORT


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif  /* !defined (GPPTYPES_H) */
/*
 *  @(#) ti.sdo.ce.ipc.dsplink; 2, 0, 1,182; 12-2-2010 21:24:23; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

