/*************************************************************/
/* codec_types.h                                             */
/*   DM350 Bigbox Test F/W Parameters                        */
/*   ------------------------------------------------------  */
/*   11/01/2005  First release by                            */
/*************************************************************/
#ifndef __CODEC_TYPES_H__
#define __CODEC_TYPES_H__

#include "imcop_types.h"
//#include "tistdtypes.h"

#define JPEGE_MAX_NUM_OVERLAYS 5

/*********************************************************/
/* Type Definitions                                      */
/*********************************************************/
/* codec enumaration */
typedef enum _CodecType {
	JPEG  = 0,
	MPEG1 = 1,
	MPEG2 = 2,
	H263  = 3,
	MPEG4 = 4
} CodecType;

typedef enum _JpegFormat {
	JPEG420  = 0,
	JPEG422  = 1,
	JPEG444  = 2,
	JPEGGRAY = 3
} JpegFormat;

/* b-iMX */
typedef enum _MERange {
	ME0      = 0, /* No search */
	ME7      = 7, /* +/- 3.5 */
	ME31     = 31 /* +/- 15.5 */
} MERange;

/* H263 option parameters */
typedef struct _BigBox_H263Option {
	/* BP */
	int gobID;
	int sizeCode; /* 2:QCIF, 3:CIF, 4:4CIF, 5:16CIF */
} BigBox_H263Option;

typedef enum _JpegEvent{
  NOERROR=0,
  HALFBUF_FULL= 1,
  END_SLICE= 2,
  ERROR_HW= 3

} JpegEvent;

/* MPEG4 option parameters */
typedef struct _BigBox_MPEG4Option {
	/* b-iMX */
	int roundingControl;
	/* QIQ */
	int acpredEnable;
	U16 acpredThr;
	/* BP */
	U1  quantType;         // quant_type
	U4  fCode;            // fcode size for vertical axis
	U3  intraDcVlcThr;     // for mp4
	U16 vopTimeIncrement; 
	U16 vopTimeResolution;
	int modulo_time_base;
    int time_increment_tmp;
} BigBox_MPEG4Option;

/* JPEG option parameters */
typedef struct _BigBox_JPEGOption {
	JpegFormat format;
	int Q;
} BigBox_JPEGOption;
typedef struct JPEGE_SeqCmdStruct{
 U16 * dat_copcmbx;
 U16 * dat_modmbx;
 U16 * dat_savedcopcmbx;
 U16 * dat_sttime;
 U16 * dat_stbufsw;
 U16 * dat_tab_addrmod;
 U16 * dat_tmp_irq2;
 U16 * dat_tmp_irq1A;
 U16 * dat_tmp_irq1B;
 U16 * dat_tmp_irq1C;
 U16 * dat_tmp_irq1P1;
 U16 * dat_tmp_irq1P2;
 U16 * dat_tmp_irq0;
 U16 * dat_int_arm;
 U16 * dat_int_copc;
 U16 * dat_int_bp;
 U16 * dat_copcrun;
 U16 * mcuRow;
 U16 * dat_tmp0;
 U16 * dat_tmp1;
 U16 * dat_tmp2;
 U16 * dat_tmp3;
 U16 * dat_mbHalfSizeX;
 U16 * dat_planar;
 U16 * dat_edma_trig_bs_addrle; 
 U16 * dat_edma_trig_bs_bitle; 
 U16 * dat_edma_trig_bs_addrlo;
 U16 * dat_edma_trig_bs_bitlo;
 U16 * dat_rotation;
 U16 * dat_rotation_cnt;
 U16 * dat_edma_y_a_addr;
 U16 * dat_edma_y_b_addr;
 U16 * dat_edma_y_c_addr;
 U16 * dat_edma_u_a_addr;
 U16 * dat_edma_u_b_addr;
 U16 * dat_edma_u_c_addr;
 U16 * dat_edma_v_a_addr;
 U16 * dat_edma_v_b_addr;
 U16 * dat_edma_v_c_addr;
 U16 * dat_edma_y_srccidx_lo;
 U16 * dat_edma_y_srccidx_hi;
 U16 * dat_edma_u_srccidx_lo;
 U16 * dat_edma_u_srccidx_hi; 
 U16 * dat_edma_v_srccidx_lo;
 U16 * dat_edma_v_srccidx_hi;
 U16 * dat_num_overlays;
 U16 * dat_overlays;
 U16 * dat_overlayIndex;
 U16 * dat_countMCUlow;
 U16 * dat_countMCUhigh;
 U16 * dat_numMCUdrawn;
 U16 * dat_rowMCU;
 U16 * dat_numMcuPerLine;
 U16 * dat_imgbuf;
 U16 * dat_bitmapTrigAddr;
 U16 * dat_bitmapTrigVal;
 U16 * dat_bitmapDstOfst;
 U16 * dat_bitmapSrcEntryLow; 
 U16 * dat_bitmapDstEntryLow;
 U16 * dat_disableOverlay;    
 U16 streamBufFlagSaved;
 U16 label_resume;
 U16 label_start;
}JPEGE_SeqCmdStruct;

/* BigBox register set parameters */
typedef struct _BigBox_CodecParam {
    U32 *HeaderScratchBuffer;
	CodecType codec;	
	//int decFlag;	    /* 0:enc, 1:dec */
	int numFrames;
	/* COPC */
	U10 mbSizeX;
	U10 mbSizeY;
	U20 predInterval;   /* 0:off, 1-:on (1 MCU unit in JPEG, 1 row unit in MPEG) */
	U2  imgMod;
	U1  seqMod;
	/* b-iMX */
	MERange searchRange;
	U16 intraThred;
	/* BP */
	U1  pictureType;	/* 0:I-picture, 1:P-picture */		
	U16 initBufPtr;
	U4  initBitPtr;
	int pingPong;
	/* Size of the stream buffer */
	int streamBufSize;

	U32 encBytes;   /* encoded bytes on Ring buffer */
	U32 totalBytes; /* precise total encoded bytes */
	U32 cumulativetotalBytes; /* precise total encoded bytes till previous frame */
	U16 format; /* Input Format */ 
	/* RCT */
	S32 d_0;            //initial value of virtual buffer d0
	U16 T_over_MB_SIZ;  //average bit rate per macroblock T/MB_SIZ
	U32 reacPrm;
	U5  rcQ_MAX; /* LOCAL MAX */
	U5  rcQ_MIN; /* LOCAL MIN */
	U32 encBits; /* encoded bits for a picture */
	U7  ratecntQ;
	U32 bitRate;
	U32 frameRate;
	int bitRateFactor;
	int rateFix;
	U7  rateFixRange;
	int gopInterval;
	U5  gQ_MAX; /* GLOBAL MAX */
	U5  gQ_MIN; /* GLOBAL MIN */
	U5  initQ;  /* initial Q */
	U5  dqDiff; /* Dquant diff */
	/* codec option parameters */
	union _opParam {
#ifdef ENABLE_MPEG4_H263
		BigBox_H263Option  h263;
#endif
		BigBox_MPEG4Option mpeg4;
	} opParam;
} BigBox_CodecParam;

typedef struct JPEGE_EdmaChan{
	U8 index;
	U8 tcc;
} JPEGE_EdmaChan;

typedef struct JPEGE_Edma{

	struct {
		JPEGE_EdmaChan imgtrans;
		JPEGE_EdmaChan copy;
		JPEGE_EdmaChan strwrite_e;
		JPEGE_EdmaChan strwrite_o;
		JPEGE_EdmaChan strwrite_d;
		JPEGE_EdmaChan errorcode;
		JPEGE_EdmaChan strovflow;
		JPEGE_EdmaChan orgread_acol_y;
		JPEGE_EdmaChan orgread_bcol_y;
		JPEGE_EdmaChan orgread_ccol_y;
		JPEGE_EdmaChan orgread_acol_u;
		JPEGE_EdmaChan orgread_bcol_u;
		JPEGE_EdmaChan orgread_ccol_u;
		JPEGE_EdmaChan orgread_acol_v;
		JPEGE_EdmaChan orgread_bcol_v;
		JPEGE_EdmaChan orgread_ccol_v;
		JPEGE_EdmaChan ovlybmap;
	} chan;

	struct {
		U8 imgtransi;
		U8 copy;
		U8 strwrite_ei;
		U8 strwrite_oi;
		U8 strwrite_di;
		U8 errorcode;
		U8 strovflow;
		U8 orgread_acol_y;
		U8 orgread_bcol_y;
		U8 orgread_ccol_y;
		U8 orgread_acol_u;
		U8 orgread_bcol_u;
		U8 orgread_ccol_u;
		U8 orgread_acol_v;
		U8 orgread_bcol_v;
		U8 orgread_ccol_v;
		U8 ovlybmap;

		U8 imgtransa;
		U8 imgtransb;
		U8 imgtransc;
		
		U8 strwrite_e0;
		U8 strwrite_e1;
		U8 strwrite_o0;
		U8 strwrite_o1;
		
		U8 strwrite_d;
		U8 orgread_acol_yb;
		U8 orgread_bcol_yb;
		U8 orgread_ccol_yb;
		U8 orgread_acol_ub;
		U8 orgread_bcol_ub;
		U8 orgread_ccol_ub;
		U8 orgread_acol_vb;
		U8 orgread_bcol_vb;
		U8 orgread_ccol_vb;

		U8 ovlybmap_reload[JPEGE_MAX_NUM_OVERLAYS];
	} entry;

} JPEGE_Edma;

typedef struct JPEGE_OverlayStruct{
	U8 Y;
	U8 Cb;
	U8 Cr;
	U16 startMCUlow;
	U16 startMCUhigh;
	U16 widthMCU;
	U16 numRowMCU;
	U16 incLow;
	U16 incHigh;
	U8 *bitmap;
} JPEGE_OverlayStruct;

typedef struct JPEGE_Overlay{
	JPEGE_OverlayStruct overlayArray[JPEGE_MAX_NUM_OVERLAYS+1];
	U8 numOverlays;
	U16 numMcuPerLine;
    U16 *cmdToModify1;
    U16 *cmdToModify2;
    U16 *cmdToModify3;
    U16 *cmdToModify1UV;
} JPEGE_Overlay;

/* BigBox register set parameters */
typedef struct _BigBox_JpegCodecParam {
	//CodecType codec;	
	int decFlag;	    /* 0:enc, 1:dec */
	//int frameNum;
	/* COPC */
	U10 mbSizeX;
	U10 mbSizeY;
	U16 width;
	U16 height;
	U32 lineOffset;
	U20 predInterval;   /* 0:off, 1-:on (1 MCU unit in JPEG, 1 row unit in MPEG) */
	U2  imgMod;
	U1  seqMod;
	/* b-iMX */
	//MERange searchRange;
	//U16 intraThred;
	/* BP */
	//U1  pictureType;	/* 0:I-picture, 1:P-picture */		
	U16 initBufPtr;
	U4  initBitPtr;
	//int pingPong;
	U32 encBytes;   /* encoded bytes on Ring buffer */
	U32 totalBytes; /* precise total encoded bytes */
	U32 curInPtrY;
	U32 curInPtrU;
	U32 curInPtrV;
	U16 planar;
	U16 lineFormat;
	U16 rotation;
	U16 customQ;
	U8 customQluma[64];
	U8 customQchroma[64];
	U32 encBits; /* encoded bits for a picture */
	JPEGE_Edma edma;
	JPEGE_Overlay overlay;
	JPEGE_SeqCmdStruct jpge_seqcmd_init;
	union {
	  BigBox_JPEGOption  jpeg;
	} opParam;
    U32 *virt_temp;
    U16 *virt_MemSwitchValHW;
    U16 *virt_errorCode; 
    U32 *virt_val;
    U32 *virt_JPGENC_TI_DM350_IprClearBit;
} BigBox_JpegCodecParam;



#endif // #ifndef __HWSET_BIGBOX_H__

