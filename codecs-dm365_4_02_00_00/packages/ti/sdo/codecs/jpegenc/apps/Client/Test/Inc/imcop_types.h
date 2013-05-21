/*************************************************************/
/* imcop_types.h                                             */
/*   DM350 IMCOP type definitions                            */
/*   ------------------------------------------------------  */
/*   09/02/2005  First release by                            */
/*************************************************************/

#ifndef __IMCOP_TYPES_H__
#define __IMCOP_TYPES_H__

/*********************************************************/
/* Utility macros                                        */
/*********************************************************/
/* Array size */
#define ARRAY_LENGTH(X) (sizeof(X)/sizeof(X[0]))

/* Register size */
#define REG_SIZE(sReg) (sizeof(sReg)/sizeof(IMCOP_Reg))

/* Unsigned Bit Extraction */
#define BITEXT(value, bitLoc, bitNum) /*(U##bitNum)*/(((value) >> (bitLoc)) & ((1 << (bitNum)) - 1))

/* Signed Bit Extraction */
#define BITEXTS(value, bitLoc, bitNum) /*(S##bitNum)*/((((S32)(value) << (32-(bitNum)-(bitLoc))) >> (32-(bitNum))))

/* Bit Field Writing */
#define WRITE_FIELD(variable, bitLoc, bitNum, value) {variable &= ~(((1 << (bitNum)) -1) << (bitLoc)); variable |= (((value) & ((1 << (bitNum)) -1))<< (bitLoc));}

/*********************************************************/
/* Type definitions                                      */
/*********************************************************/

/* BOOL type */
#if 0
typedef enum _BOOL {
    FALSE = 0,
    TRUE = 1
} BOOL;
#endif

typedef int BOOL;
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

/* data types for MS VC++ */
#ifdef _MSC_VER
typedef signed _int8 S8;
typedef unsigned _int8 U8;
typedef signed _int16 S16;
typedef unsigned _int16 U16;
typedef signed _int32 S32;
typedef unsigned _int32 U32;
typedef signed _int64 S64;
typedef unsigned _int64 U64;
#endif                          /* _MSC_VER */

typedef signed char S8;
typedef unsigned char U8;
typedef signed short S16;
typedef unsigned short U16;
typedef signed int S32;
typedef unsigned int U32;
typedef signed long long S64;
typedef unsigned long long U64;

/* integer types with bit-width not equal to a multiple of 8 */
/* unsigned 1 to 7 bit */
typedef U8 U1;
typedef U8 U2;
typedef U8 U3;
typedef U8 U4;
typedef U8 U5;
typedef U8 U6;
typedef U8 U7;

/* signed 1 to 7 bit */
typedef S8 S1;
typedef S8 S2;
typedef S8 S3;
typedef S8 S4;
typedef S8 S5;
typedef S8 S6;
typedef S8 S7;

/* unsigned 9 to 15 bit */
typedef U16 U9;
typedef U16 U10;
typedef U16 U11;
typedef U16 U12;
typedef U16 U13;
typedef U16 U14;
typedef U16 U15;

/* unsigned 9 to 15 bit */
typedef S16 S9;
typedef S16 S10;
typedef S16 S11;
typedef S16 S12;
typedef S16 S13;
typedef S16 S14;
typedef S16 S15;

typedef U32 U17;
typedef U32 U18;
typedef U32 U19;
typedef U32 U20;
typedef U32 U21;
typedef U32 U22;
typedef U32 U23;
typedef U32 U24;
typedef U32 U25;
typedef U32 U26;
typedef U32 U27;
typedef U32 U28;
typedef U32 U29;
typedef U32 U30;
typedef U32 U31;

typedef U64 U48;

typedef S32 S17;
typedef S32 S18;
typedef S32 S19;
typedef S32 S20;
typedef S32 S21;
typedef S32 S22;
typedef S32 S23;
typedef S32 S24;
typedef S32 S25;
typedef S32 S26;
typedef S32 S27;
typedef S32 S28;
typedef S32 S29;
typedef S32 S30;
typedef S32 S31;

/* IMCOP configuration register */
typedef volatile unsigned short IMCOP_Reg;
typedef volatile unsigned int IMCOP_Reg32;

/* IMCOP memories */
typedef signed char IMCOP_Mem;
typedef signed char IMCOP_Mem8;
typedef signed short IMCOP_Mem16;
typedef signed int IMCOP_Mem32;

#endif                          // #ifndef __IMCOP_TYPES_H__
