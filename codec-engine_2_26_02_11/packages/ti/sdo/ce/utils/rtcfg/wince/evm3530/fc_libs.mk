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
#  ======== ti.sdo.ce.utils.rtcfg.wince.evm3530/fc_libs.mk ========
#  This file is included by rtcfg example makefiles that build for WinCE. It
#  contains of the framework components libraries to be linked in with the app.
#  The symbols PROFILE (debug or release) and TRACE_PREFIX (_trace or empty
#  string), must be defined in the makefile that includes this file.
#
#  Note: We use the cpu-copy versions of the ACPY3 and DMAN3 libraries, since
#  there is no EDMA3 on the ARM side of OMAP3530. The dman3Cfg.av4TC library
#  is actually a cpu-copy version, even though its name does not indicate
#  this.
#


FC_LIBS = \
	"$(FC_REPO)/ti/sdo/fc/acpy3/lib/$(FC_PROFNAME)/acpy3cpu.av4TCE" \
	"$(FC_REPO)/ti/sdo/fc/memutils/lib/$(FC_PROFNAME)/memutils.av4TCE" \
	"$(FC_REPO)/ti/sdo/fc/dman3/lib/$(FC_PROFNAME)/dman3.av4TCE" \
	"$(FC_REPO)/ti/sdo/fc/rman/lib/$(FC_PROFNAME)/rman.av4TCE" \
	"$(FC_REPO)/ti/sdo/fc/ires/nullresource/lib/$(FC_PROFNAME)/nullres.av4TCE" \
	"$(FC_REPO)/ti/sdo/utils/trace/lib/$(PROFILE)/gt.av4TCE"
