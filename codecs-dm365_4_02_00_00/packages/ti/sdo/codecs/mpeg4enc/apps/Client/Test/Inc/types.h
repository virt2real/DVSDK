/************************************************************************************/
/*                  OMAP-DM290 Evaluation Program                                   */
/*                                                                                  */
/*                  File Name : types.h                                             */
/*                                                                                  */
/************************************************************************************/
/*  << Revision Histrory >>                                                         */
/*                                                                                  */
/*  Revision    Date        Comments                                                */
/*  ========    ==========  ======================================================= */
/*  Rev 0.0     04/28/2005  First Revision                                          */
/************************************************************************************/
#ifndef	__TYPES_H__
#define	__TYPES_H__

typedef	char				CHAR;
typedef	char				Int8;
typedef	char				INT8;
typedef	unsigned char		UCHAR;
typedef	unsigned char		Uint8;
typedef	unsigned char		UINT8;
typedef	short				SHORT;
typedef	short				Int16;
typedef	short				INT16;
typedef	unsigned short		USHORT;
typedef	unsigned short		Uint16;
typedef	unsigned short		UINT16;
typedef	int					INT;
typedef	int					Int32;
typedef	int					INT32;
typedef	unsigned int		UINT;
typedef	unsigned int		Uint32;
typedef	unsigned int		UINT32;
typedef	long				LONG;
typedef	unsigned long		ULONG;
typedef	unsigned char		BYTE;
typedef	unsigned short		WORD;
typedef	enum {FALSE, TRUE}	BOOL;

#define	REG8	*(volatile unsigned char *)		// for  8bits Register
#define	REG16	*(volatile unsigned short *)	// for 16bits Register
#define	REG32	*(volatile unsigned long *)		// for 32bits Register
#define REG		*(volatile unsigned short*)		// for 16bits Register

#define SUCCESS		(0)
#define FAIL		(-1)

#endif
