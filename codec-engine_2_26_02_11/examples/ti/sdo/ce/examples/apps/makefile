# 
#  Copyright (c) 2010, Texas Instruments Incorporated
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
# 
include ../../../../../xdcpaths.mak

all:
%::
	echo DEVICES=$(DEVICES)
	$(MAKE) -C speech $@
	$(MAKE) -C speech_copy $@
	$(MAKE) -C image_copy $@
	$(MAKE) -C video_copy $@
ifneq (,$(findstring DM6446,$(DEVICES)))
# The following two use server video_copy.x64P, which isn't ready
# to be used w/ Engine.createFromServer (needs to be a package?)
#	$(MAKE) -C video_copy/dualcpu_separateconfig_dll/configured_CE_subsystem $@
#	$(MAKE) -C video_copy/dualcpu_separateconfig/configured_CE_subsystem $@
endif
	$(MAKE) -C audio_copy $@
	$(MAKE) -C scale $@
ifeq ($(DEVICES_DUALCPU), 1)
	$(MAKE) -C server_api_example $@
	$(MAKE) -C speech_copy_LAD $@
#	$(MAKE) -C server_trace $@
endif
	$(MAKE) -C video2_copy $@
	$(MAKE) -C video1_copy $@
	$(MAKE) -C video1_copy/rtcfg_DM365 $@
	$(MAKE) -C video1_copy/rtcfg_local_evm3530_linux $@
	$(MAKE) -C video1_copy/rtcfg_local_evm3530_wince $@
	$(MAKE) -C video1_copy/rtcfg_remote_evm3530_linux $@
	$(MAKE) -C video1_copy/rtcfg_remote_evm3530_wince $@
	$(MAKE) -C image1_copy $@
	$(MAKE) -C audio1_copy/sync $@
	$(MAKE) -C audio1_copy/async $@
	$(MAKE) -C audio1_ires $@
	$(MAKE) -C audio1_ires/rtcfg_DM365 $@
	$(MAKE) -C audio1_ires/rtcfg_local_evm3530_linux $@
	$(MAKE) -C audio1_ires/rtcfg_local_evm3530_wince $@
	$(MAKE) -C audio1_ires/rtcfg_PC $@
	$(MAKE) -C speech1_copy $@
	$(MAKE) -C speech1_copy/rtcfg_DM365 $@
	$(MAKE) -C speech1_copy/rtcfg_local_evm3530_linux $@
	$(MAKE) -C speech1_copy/rtcfg_local_evm3530_wince $@
	$(MAKE) -C speech1_copy/rtcfg_PC $@
	$(MAKE) -C speech1_copy/rtcfg_remote_evm3530_linux $@
	$(MAKE) -C speech1_copy/rtcfg_remote_evm3530_wince $@
	$(MAKE) -C video2split_copy $@
	$(MAKE) -C vidtranscode $@
	$(MAKE) -C vidanalytics $@
	$(MAKE) -C universal_copy $@

#
#  @(#) ti.sdo.ce.examples.apps; 1, 0, 0,264; 12-2-2010 21:19:04; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

#

