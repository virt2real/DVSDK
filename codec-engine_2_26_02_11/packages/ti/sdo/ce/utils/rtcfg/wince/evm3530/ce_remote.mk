# --COPYRIGHT--,BSD
#  Copyright (c) $(CPYYEAR), Texas Instruments Incorporated
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#
#  *  Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#
#  *  Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#
#  *  Neither the name of Texas Instruments Incorporated nor the names of
#     its contributors may be used to endorse or promote products derived
#     from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
#  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
#  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
#  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# --/COPYRIGHT--
#
#  ======== ti.sdo.ce.utils.rtcfg.wince.evm3530/ce_remote.mk ====
#  This file is included by rtcfg example makefiles that build for WinCE. It
#  contains the codec engine and framework components libraries to be linked
#  in with the app.
#


CE_LIBS = \
	"$(CE_REPO)/ti/sdo/ce/audio/lib/$(PROFILE)/audio.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/image/lib/$(PROFILE)/image.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/speech/lib/$(PROFILE)/speech.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/video/lib/$(PROFILE)/video.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/audio1/lib/$(PROFILE)/auddec1.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/audio1/lib/$(PROFILE)/audenc1.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/image1/lib/$(PROFILE)/imgdec1.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/image1/lib/$(PROFILE)/imgenc1.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/speech1/lib/$(PROFILE)/sphdec1.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/speech1/lib/$(PROFILE)/sphenc1.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/video1/lib/$(PROFILE)/viddec1.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/video1/lib/$(PROFILE)/videnc1.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/video2/lib/$(PROFILE)/viddec2.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/universal/lib/$(PROFILE)/universal.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/vidanalytics/lib/$(PROFILE)/vidanalytics.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/vidtranscode/lib/$(PROFILE)/vidtranscode.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/video2/split/lib/debug/viddec2back.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/video2/split/lib/debug/viddec2front.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/lib/$(PROFILE)/ce.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/alg/lib/$(PROFILE)/Algorithm_noOS.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/alg/lib/$(PROFILE)/alg.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/ipc/dsplink/lib/$(PROFILE)/ipc_dsplink_3530.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/osal/wince/lib/$(PROFILE)/osal_wince.av4TCE" \
	"$(FC_REPO)/ti/sdo/fc/acpy3/lib/$(PROFILE)/acpy3.av4TCE" \
	"$(FC_REPO)/ti/sdo/fc/memutils/lib/$(PROFILE)/memutils.av4TCE" \
	"$(FC_REPO)/ti/sdo/fc/dman3/lib/$(PROFILE)/dman3Cfg.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/node/lib/$(PROFILE)/node.av4TCE" \
	"$(CE_REPO)/ti/sdo/ce/utils/xdm/lib/$(PROFILE)/XdmUtils.av4TCE" \
	"$(FC_REPO)/ti/sdo/utils/trace/lib/$(PROFILE)/gt.av4TCE" \
	"$(LPM_REPO)/ti/bios/power/lib/$(PROFILE)/lpm.av4TCE" \
	"$(WINCEUTILS_REPO)/ti/sdo/winceutils/cmem/user/obj/ARMV4I/retail/cmem.lib" \
	"$(DSPLINK_INSTALL_DIR)/dsplink/gpp/export/BIN/WinCE/OMAP3530/RELEASE/dsplinkapi.lib"


