/* itt_tb_chk_sum.h - header file for itt_tb_MD5.c
 */

/* Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
rights reserved.

License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD5 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.

License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD5 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.

RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

These notices must be retained in any copies of any part of this
documentation and/or software.
 */

#ifndef ITT_TB_CHK_SUM_H
#define ITT_TB_CHK_SUM_H

void Calculate_MD5_CkSum_buf(unsigned char *inbuf,
                             unsigned int inbufwidth,
                             unsigned int inbufstride,
                             unsigned int inbufheight,
                             unsigned char *cksum_p);

#endif // ITT_TB_CHK_SUM_H
