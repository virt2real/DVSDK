/*
 * dvtbResizer.h
 *
 * Resizer Interface implementation
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#include "dvtbResizer.h"
#include "dvtbMemory.h"

#define PAGE_SIZE getpagesize()

#define RDRV_RESZ_SPEC__MAX_FILTER_COEFF 32

/* For resizing between */
short gRDRV_reszFilter4TapHighQuality[RDRV_RESZ_SPEC__MAX_FILTER_COEFF]= {
	0, 256, 0, 0, -6, 246, 16, 0, -7, 219, 44, 0, -5, 179, 83, -1, -3,
	130, 132, -3, -1, 83, 179, -5, 0, 44, 219, -7, 0, 16, 246, -6
};
short gRDRV_reszFilter7TapHighQuality[RDRV_RESZ_SPEC__MAX_FILTER_COEFF] = {
	-1, 19, 108, 112, 19, -1, 0, 0, 0, 6, 88, 126, 37, -1, 0, 0,
	0, 0, 61, 134, 61, 0, 0, 0, 0, -1, 37, 126, 88, 6, 0, 0
};

DvevmStRetCode
dvtb_resizerOutBuffAlloc(DvevmStResizerInfo *vpRsz, DvevmStXdmBuffer *rszBuf ,IVIDEO1_BufDescIn *rszBufDesc)
{
	int size;

        switch(vpRsz->rszInputFormat)
        {
                case XDM_YUV_422ILE:
			rszBuf->numBufs = 1;
			size = (vpRsz->params.out_hsize * vpRsz->params.out_vsize) << 1;

			rszBuf->bufSizes[0] = ALIGN(size,PAGE_SIZE);
			if (DVEVM_ST_FAIL == dvtb_allocCmem(rszBuf))
			{
				SYS_ERROR("Unable to allocate memory for resizer buffer\n");
				return DVEVM_ST_FAIL;
				break;
			}
			rszBufDesc->numBufs            = rszBuf->numBufs;
			rszBufDesc->bufDesc[0].bufSize = size;
			rszBufDesc->bufDesc[0].buf     = (XDAS_Int8 *)rszBuf->bufs[0];
	
                        break;

                case XDM_YUV_420P:
			rszBuf->numBufs = 3;
			size = vpRsz->params.out_hsize * vpRsz->params.out_vsize;
			rszBuf->bufSizes[0] = ALIGN(size,PAGE_SIZE);
			rszBuf->bufSizes[1] = ALIGN((size >> 2),PAGE_SIZE);
			rszBuf->bufSizes[2] = ALIGN((size >> 2),PAGE_SIZE);
			if (DVEVM_ST_FAIL == dvtb_allocCmem(rszBuf))
			{
				SYS_ERROR("Unable to allocate memory for resizer buffer\n");
				return DVEVM_ST_FAIL;
				break;
			}
			rszBufDesc->numBufs            = rszBuf->numBufs;
			rszBufDesc->bufDesc[0].bufSize = size;
			rszBufDesc->bufDesc[0].buf     = (XDAS_Int8 *)rszBuf->bufs[0];
			rszBufDesc->bufDesc[1].bufSize = size >> 2;
			rszBufDesc->bufDesc[1].buf     = (XDAS_Int8 *)rszBuf->bufs[1];
			rszBufDesc->bufDesc[2].bufSize = size >> 2;
			rszBufDesc->bufDesc[2].buf     = (XDAS_Int8 *)rszBuf->bufs[2];
                        break;

                default:
                        SYS_ERROR("Resizer: Input format %d is not supported  \n",vpRsz->rszInputFormat);
                        dvtb_resizerClose(vpRsz);
                        return DVEVM_ST_FAIL;
        }


	return DVEVM_ST_SUCCESS;	
}

DvevmStRetCode
dvtb_resizerSetup(DvevmStResizerInfo *vpRsz)
{

	int i = 0;

	vpRsz->rszFd = DVEVM_ST_FAIL;

	SYS_DEBUG("opening resize device\n");
	vpRsz->rszFd = open(vpRsz->resizeDevice, O_RDWR);
	if (DVEVM_ST_FAIL == vpRsz->rszFd)
	{
		SYS_ERROR("Cannot open resize device <%s> \n",vpRsz->resizeDevice);
		return DVEVM_ST_FAIL;
	}

	/* Set Parameters */
	vpRsz->params.in_hsize            = vpRsz->rszInWidth;
	vpRsz->params.in_vsize            = vpRsz->rszInHeight;
	vpRsz->params.vert_starting_pixel = 0;
	vpRsz->params.horz_starting_pixel = 0;
	vpRsz->params.cbilin              = 0;
	vpRsz->params.pix_fmt             = RSZ_PIX_FMT_UYVY;
	vpRsz->params.out_hsize           = vpRsz->rszOutWidth;
	vpRsz->params.out_vsize           = vpRsz->rszOutHeight;
	vpRsz->params.hstph               = 0;
	vpRsz->params.vstph               = 0;
	/* As we are downsizing, we put */
	for (i = 0; i < RDRV_RESZ_SPEC__MAX_FILTER_COEFF; i++)
		vpRsz->params.tap4filt_coeffs[i] = gRDRV_reszFilter4TapHighQuality[i];

	for (i = 0; i < RDRV_RESZ_SPEC__MAX_FILTER_COEFF; i++)
		vpRsz->params.tap7filt_coeffs[i] = gRDRV_reszFilter7TapHighQuality[i];

	vpRsz->params.yenh_params.type = 0;
	vpRsz->params.yenh_params.gain = 0;
	vpRsz->params.yenh_params.slop = 0;
	vpRsz->params.yenh_params.core = 0;

	switch(vpRsz->rszInputFormat)
	{
		case XDM_YUV_422ILE:
//			if(vpRsz->params.in_hsize*vpRsz->params.in_vsize < vpRsz->params.out_hsize*vpRsz->params.out_vsize)
//				isUpsample = 1;

//			vpRsz->params.cbilin              = isUpsample;
			vpRsz->params.in_pitch  = (vpRsz->params.in_hsize << 1);
			vpRsz->params.out_pitch = (vpRsz->params.out_hsize << 1);
			vpRsz->params.inptyp    = RSZ_INTYPE_YCBCR422_16BIT;
			if(DVEVM_ST_FAIL == dvtb_configureResizer(vpRsz))
			{
				SYS_ERROR("Resizer: Unable to configure \n");
				dvtb_resizerClose(vpRsz);
				return DVEVM_ST_FAIL;
			}
			break;

		case XDM_YUV_420P:
			SYS_ERROR("Resizer: Format %d Not supported \n",vpRsz->rszInputFormat);
			dvtb_resizerClose(vpRsz);

			vpRsz->params.in_pitch  = vpRsz->params.in_vsize;
			vpRsz->params.out_pitch = vpRsz->params.out_hsize;
			vpRsz->params.inptyp    = RSZ_INTYPE_PLANAR_8BIT;
			break;

		default:
			SYS_ERROR("Resizer: Input format %d is not supported  \n",vpRsz->rszInputFormat);
			dvtb_resizerClose(vpRsz);
			return DVEVM_ST_FAIL;
	}

	SYS_OUT("Resizer initialized, fd = %d\n", vpRsz->rszFd);
	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_configureResizer(DvevmStResizerInfo *vpRsz)
{

	struct v4l2_requestbuffers creqbuf;
	int read_exp;
	
	SYS_DEBUG("Resizer:in_hsize  %d \n",vpRsz->params.in_hsize);
	SYS_DEBUG("Resizer:in_vsize  %d \n",vpRsz->params.in_vsize);
	SYS_DEBUG("Resizer:out_hsize %d \n",vpRsz->params.out_hsize);
	SYS_DEBUG("Resizer:out_vsize %d \n",vpRsz->params.out_vsize);
	SYS_DEBUG("Resizer:in_pitch  %d \n",vpRsz->params.in_pitch);
	SYS_DEBUG("Resizer:out_pitch %d \n",vpRsz->params.out_pitch);

        if(ioctl(vpRsz->rszFd, RSZ_S_PARAM, &vpRsz->params))
        {
                SYS_ERROR("Resizer: Error in RSZ_S_PARAM\n");
                dvtb_resizerClose(vpRsz);
                return DVEVM_ST_FAIL;
        }

        read_exp = 0x0;
        if(ioctl(vpRsz->rszFd, RSZ_S_EXP, &read_exp))
        {
                SYS_ERROR("Resizer: Error in RSZ_S_EXP\n");
                dvtb_resizerClose(vpRsz);
                return DVEVM_ST_FAIL;
        }

        creqbuf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        creqbuf.memory = V4L2_MEMORY_USERPTR;
        creqbuf.count = 2;
        /* Request input buffer */
        if(ioctl (vpRsz->rszFd, RSZ_REQBUF, &creqbuf) < 0)
        {
                SYS_ERROR("Resizer: Error in RSZ_REQBUF\n");
                dvtb_resizerClose(vpRsz);
                return DVEVM_ST_FAIL;
        }

	return DVEVM_ST_SUCCESS;

}

DvevmStRetCode
dvtb_resizeImage(DvevmStResizerInfo *vpRsz, IVIDEO1_BufDescIn *inBufDesc, IVIDEO1_BufDescIn *outBufDesc)
{
        switch(vpRsz->rszInputFormat)
        {
                case XDM_YUV_422ILE:
			if(DVEVM_ST_FAIL == dvtb_resizeBuff(vpRsz, (char *)inBufDesc->bufDesc[0].buf, inBufDesc->bufDesc[0].bufSize, (char *)outBufDesc->bufDesc[0].buf, outBufDesc->bufDesc[0].bufSize))
			{
				SYS_ERROR("Resizer: Fail to resize buffer \n");	
				dvtb_resizerClose(vpRsz);
				return DVEVM_ST_FAIL;
			}
                        break;

                case XDM_YUV_420P:

			//Luma
		        vpRsz->params.in_hsize            = vpRsz->rszInWidth;
		        vpRsz->params.in_vsize            = vpRsz->rszInHeight;
                        vpRsz->params.in_pitch            = vpRsz->params.in_hsize;
		        vpRsz->params.out_hsize           = vpRsz->rszOutWidth;
		        vpRsz->params.out_vsize           = vpRsz->rszOutHeight;
                        vpRsz->params.out_pitch           = vpRsz->params.out_hsize;
                        vpRsz->params.inptyp              = RSZ_INTYPE_PLANAR_8BIT;
                        if(DVEVM_ST_FAIL == dvtb_configureResizer(vpRsz))
                        {
                                SYS_ERROR("Resizer: Unable to configure \n");
                                dvtb_resizerClose(vpRsz);
                                return DVEVM_ST_FAIL;
                        }
                        if(DVEVM_ST_FAIL == dvtb_resizeBuff(vpRsz, (char *)inBufDesc->bufDesc[0].buf, inBufDesc->bufDesc[0].bufSize, (char *)outBufDesc->bufDesc[0].buf, outBufDesc->bufDesc[0].bufSize))
                        {
                                SYS_ERROR("Resizer: Fail to resize Luma buffer \n");
                                dvtb_resizerClose(vpRsz);
                                return DVEVM_ST_FAIL;
                        }

			//chroma
                        vpRsz->params.in_hsize            = vpRsz->rszInWidth / 2;
                        vpRsz->params.in_vsize            = vpRsz->rszInHeight / 2;
                        vpRsz->params.in_pitch            = vpRsz->params.in_hsize;
                        vpRsz->params.out_hsize           = vpRsz->rszOutWidth / 2;
                        vpRsz->params.out_vsize           = vpRsz->rszOutHeight / 2;
                        vpRsz->params.out_pitch           = vpRsz->params.out_hsize;
                        if(DVEVM_ST_FAIL == dvtb_resizeBuff(vpRsz, (char *)inBufDesc->bufDesc[1].buf, inBufDesc->bufDesc[1].bufSize, (char *)outBufDesc->bufDesc[1].buf, outBufDesc->bufDesc[1].bufSize))
                        {
                                SYS_ERROR("Resizer: Fail to resize Cb buffer \n");
                                dvtb_resizerClose(vpRsz);
                                return DVEVM_ST_FAIL;
                        }

                        if(DVEVM_ST_FAIL == dvtb_resizeBuff(vpRsz, (char *)inBufDesc->bufDesc[2].buf, inBufDesc->bufDesc[2].bufSize, (char *)outBufDesc->bufDesc[2].buf, outBufDesc->bufDesc[2].bufSize))
                        {
                                SYS_ERROR("Resizer: Fail to resize Cr buffer \n");
                                dvtb_resizerClose(vpRsz);
                                return DVEVM_ST_FAIL;
                        }
                        break;

                default:
                        SYS_ERROR("Resizer: Input format %d is not supported  \n",vpRsz->rszInputFormat);
                        dvtb_resizerClose(vpRsz);
                        return DVEVM_ST_FAIL;
        }
	return DVEVM_ST_SUCCESS;

}

DvevmStRetCode
dvtb_resizeBuff(DvevmStResizerInfo *vpRsz, char *inBuff, int inBuffSize, char *outBuff, int outBuffSize)
{
	struct v4l2_buffer vbuffer;
	int ret = 0;
	
	ASSERT(inBuff != NULL);
	ASSERT(outBuff != NULL);

	memset(&vbuffer,0x00,sizeof(vbuffer));

	vbuffer.type      = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	vbuffer.memory    = V4L2_MEMORY_USERPTR;
	vbuffer.index     = 0;

        ret = ioctl(vpRsz->rszFd, RSZ_QUERYBUF, &vbuffer);
        if(ret < 0)
        {
                SYS_ERROR("Resizer: Error in RSZ_QUERYBUF(%d) for index %d \n",ret, vbuffer.index);
                dvtb_resizerClose(vpRsz);
                return DVEVM_ST_FAIL;
        }
	vbuffer.index     = 0;
	vbuffer.m.userptr = (unsigned int)inBuff;

        ret = ioctl(vpRsz->rszFd, RSZ_QUEUEBUF, &vbuffer);
        if(ret < 0)
        {
                SYS_ERROR("Resizer: Error in RSZ_QUEUEBUF(%d) for index %d \n",ret, vbuffer.index);
                dvtb_resizerClose(vpRsz);
                return DVEVM_ST_FAIL;
        }

	vbuffer.index     = 1;
	vbuffer.m.userptr = (unsigned int)outBuff;

	ret = ioctl(vpRsz->rszFd, RSZ_QUEUEBUF, &vbuffer);
	if(ret < 0)
	{
		SYS_ERROR("Resizer: Error in RSZ_QUEUEBUF(%d) for index %d \n",ret, vbuffer.index);
		dvtb_resizerClose(vpRsz);
		return DVEVM_ST_FAIL;
	}

	if(ioctl(vpRsz->rszFd, RSZ_RESIZE, NULL))
	{
		SYS_ERROR("Resizer: Error in RSZ_RESIZE\n");
		dvtb_resizerClose(vpRsz);
		return DVEVM_ST_FAIL;
	}
	
	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_resizerClose(DvevmStResizerInfo *vpRsz)
{
	ASSERT(vpRsz != NULL);

	if (vpRsz->rszFd > 0)
	{
		close(vpRsz->rszFd);
		vpRsz->rszFd = DVEVM_ST_FAIL;
	}

	return DVEVM_ST_SUCCESS;
}

