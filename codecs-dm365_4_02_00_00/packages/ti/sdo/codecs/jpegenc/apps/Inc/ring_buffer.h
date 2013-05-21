/************************************************************************************/
/*                       TMS320DM350/320/275 Evaluation Program                     */
/*                                                                                  */
/*                         File Name : ring_buffer.h                                */
/*                                                                                  */
/************************************************************************************/
/*     << Revision Histrory >>                                                      */
/*                                                                                  */
/*      Revision        Date            Comments                                    */
/*      ========        ==========      ============================================*/
/*      Rev 1.0         02/14/2006      Imported from DM275 version and simplified. */
/************************************************************************************/
#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__


// type definitions
typedef enum _RINGBUF_MEDIA {
	RINGBUF_SDRAM = 0
} RINGBUF_MEDIA;

typedef enum _RINGBUF_DIR
{
	RINGBUF_FORWARD = 0,
	RINGBUF_REVERSE
} RINGBUF_DIR;

typedef enum _RINGBUF_AVAIL
{
	RINGBUF_STOP	= 0,
	RINGBUF_PLAY	= 1,
	RINGBUF_REC		= 2
} RINGBUF_AVAIL;

typedef enum _RINGBUF_RET
{
	RINGBUF_NML_OP		     = 0,
	RINGBUF_EOF			     = 1,
	RINGBUF_OVER_RUN		 = 2,
	RINGBUF_WRITE_ERR		 = -2,
	RINGBUF_PRG_ERR			 = 0xFFFF,
	RINGBUF_FILE_OPEN_FAIL   = -1
} RINGBUF_RET;

// Struct Variable
typedef struct _RINGBUF_STAT {
#if 0
	// File Information
	char 	filename[256];
	FILE 	*fp;
#endif

	// Buffer Information Variables specified by user
	U32				buf_head_addr;	// Ring Buffer Head Address 
	U32				media_head_addr;// Source Head Address 
	U32				buf_size;		// Ring Buffer Size (buf_size >= trns_size * 2)
	U32				trns_size;		// Transfer Size at one time
	RINGBUF_MEDIA	media;			// Source Media
	U8				format;			// Format (Now not used)
	RINGBUF_AVAIL	available;
	S32				trns_request;	// number of transfer requests (-1: no use of this feature) 
	
	// realtime status. User should modify this.
	U32				curr_buf_ptr;

	// Play Information Variables changing at playing. User must not modify them.
	U32				media_ptr;		// Source Pointer for Next Transfer (media side)
	U32				buf_ptr;		// Destination Pointer for Next Transfer (ring buffer)
	U32				buf_tail_addr;	// Ring Buffer Tail Address;
	U32				next_trns;		// 
	RINGBUF_DIR		direction;		// Play Direction
	RINGBUF_RET		flag;
	U8				id;
} RINGBUF_STAT;


// Functions
RINGBUF_RET JPEGENC_TI_ringbuf_play_init (RINGBUF_STAT *stat);
RINGBUF_RET JPEGENC_TI_ringbuf_rec_init(RINGBUF_STAT *stat);
RINGBUF_RET ringbuf_play_status_update(const U32 current_decoded_size, RINGBUF_STAT* stat);
RINGBUF_RET JPEGENC_TI_ringbuf_change_direction(RINGBUF_DIR new_direction, RINGBUF_STAT* stat);
RINGBUF_RET JPEGENC_TI_ringbuf_rec_post(S32 final_decoded_size, RINGBUF_STAT *stat);
#define ring_buffer_file_size(x) (x->fp->efrtfz)

#endif // __RING_BUFFER_H__
