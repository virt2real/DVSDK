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
#
#  ======== speech1_copy.rtcfg_local_evm3530_wince/makefile ========
#  GNUmake-based makefile
#

#
# EXAMPLES_ROOTDIR should be set to the examples directory under your
# CE_INSTALL_DIR.
#
EXAMPLES_ROOTDIR ?= $(CURDIR)/../../../../../../..

#
#  Include xdcpaths.mak if it exists. This file defines package paths and
#  build rules.  If xdcpaths.mak does not exist the variables must be set on
#  the command line.
#
-include $(EXAMPLES_ROOTDIR)/xdcpaths.mak

#
#  ======== define all the repositories needed by this example ========
#
XDCTOOLS_REPO   ?= $(XDC_INSTALL_DIR)/packages
CE_REPO         ?= $(CE_INSTALL_DIR)/packages

#
#  Make sure CE_INSTALL_DIR was set properly. By using "-include" to include
#  xdcpaths.mak, no error message will be given if xdcpaths.mak is not found,
#  and in that case, the user must have set the environment variables, for
#  example, on the command line.
# 
ERRMSG = which is invalid (could not find file "$(TEST_FILE)"). Set this in <codec engine examples>/xdcpaths.mak! If you intended to use xdcpaths.mak, also please make sure that EXAMPLES_ROOTDIR is set correctly in this makefile. See the build documentation to correct this error.
TEST_FILE := $(CE_REPO)/ti/sdo/ce/package.xdc
ifeq ($(wildcard $(TEST_FILE)),)
    $(error CE_INSTALL_DIR is set to "$(CE_INSTALL_DIR)", $(ERRMSG))
endif


ifeq ($(USING_CETOOLS),0)

REPO_PATH = \
	$(XDCTOOLS_REPO) \
	$(CE_REPO) \
	$(XDAIS_INSTALL_DIR)/packages \
	$(FC_INSTALL_DIR)/packages \
	$(WINCEUTILS_INSTALL_DIR)/packages \
	$(LPM_INSTALL_DIR)/packages \
	$(EXAMPLES_ROOTDIR)

FC_REPO = $(FC_INSTALL_DIR)/packages
WINCEUTILS_REPO ?= $(WINCEUTILS_INSTALL_DIR)/packages

else

REPO_PATH = \
	$(XDCTOOLS_REPO) \
	$(CE_REPO) \
	$(CE_INSTALL_DIR)/cetools/packages \
	$(EXAMPLES_ROOTDIR)

FC_REPO = $(CE_INSTALL_DIR)/cetools/packages
WINCEUTILS_REPO ?= $(CE_INSTALL_DIR)/cetools/packages

endif

#
#  ======== standard macros ========
#
ECHO    ?= echo
MKDIR   ?= mkdir
RM      ?= rm -f
RMDIR   ?= rm -rf

ifneq (clean,$(MAKECMDGOALS))
ifneq (,$(PROFILE))
ifeq (,$(wildcard bin/$(PLAT)/$(PROFILE)))
    $(shell $(MKDIR) -p bin/$(PLAT)/$(PROFILE))
endif
endif
endif

.PHONY: nothing

#
#  ======== microsoft.targets.arm.WinCE ========
#
SUFFIX = v4TCE

WINCE_CCCMD ?= $(WINCE_ROOTDIR)/sdk/bin/i386/arm/cl.exe -nologo -c

COPTS = -Gy -GF -D_CRT_SECURE_NO_DEPRECATE -D_USE_32BIT_TIME_T -DUNICODE  -D_UNICODE -DUNDER_CE=600 -D_WIN32_WCE=0x600 -DWIN32 -DSTRICT -DARM -DARMV4I  -D_ARM_ -DINTERNATIONAL -DINTLMSG_CODEPAGE=1252 -Zc:wchar_t- -Zc:forScope- -wd4867 -wd4430 -MT -U_MT -W3 /GR- -QRarch4T -DTHUMBSUPPORT -QRimplicit-import- -QRinterwork-return /GS

DEFS = -Dfar= -Dxdc_target_name__=WinCE -Dxdc_target_types__=microsoft/targets/arm/std.h

INCS = -I. -I$(WINCE_PROJECTROOT)/cesysgen/sdk/inc $(addprefix -I,$(REPO_PATH))

CCPROFILE.debug = -Od -Z7 -D_DEBUG -DDEBUG
CCPROFILE.release = -O2 -DNDEBUG=1

CC = $(WINCE_CCCMD) $(COPTS) $(DEFS) $(CCPROFILE.$(PROFILE)) $(INCS)

WINCE_LNKCMD ?= $(WINCE_ROOTDIR)/sdk/bin/i386/arm/link -nologo
LINKPROFILE.debug = -debug -debugtype:cv,fixup coredll.lib corelibc.lib
LINKPROFILE.release = coredll.lib corelibc.lib

LOPTS = -libpath:$(WINCE_PROJECTROOT)/cesysgen/sdk/lib/ARMV4I/retail -base:0x00010000 -MERGE:.rdata=.text -MERGE:.astart=.text -align:4096 -ignore:4001,4070,4078,4086,4089,4096,4099,4108,4229 /STACK:65536,4096 /LARGEADDRESSAWARE -incremental:no /opt:ref -SUBSYSTEM:WINDOWSCE,6.00 -nodefaultlib -entry:mainCRTStartup

LNK = $(WINCE_LNKCMD) $(LINKPROFILE.$(PROFILE))

#
#  ======== enable/disable trace ========
#
#  Set to TRACE = 1 to build with framework components trace libraries, set
#  TRACE = 0 to link with non-trace libraries.
#
TRACE = 1

ifneq ($(TRACE), 0)

TRACE_PREFIX = _trace
ifeq ($(PROFILE), debug)
FC_PROFNAME = debug_trace
else
FC_PROFNAME = trace
endif

else
TRACE_PREFIX =
endif

#
# Include makefile that has definitions for apps with only local algs. If
# there are any remote algs, use ce_remote.mk instead.
#
include $(CE_REPO)/ti/sdo/ce/utils/rtcfg/wince/evm3530/ce_local.mk

#
# Include makefile for framework components libraries
#
include $(CE_REPO)/ti/sdo/ce/utils/rtcfg/wince/evm3530/fc_libs.mk

#
#  ======== example sources ========
#
#  This example is built with the following source files:
#
#  $(CE_REPO)/ti/sdo/ce/utils/rtcfg/
#      rtcfg.c
#      rtcfg_wince.c
#      rtcfg_dman3.c
#      rtcfg_rman.c
#
#      The source files in $(CE_REPO)/ti/sdo/ce/utils/rtcfg are run-time
#      configuration files.  These files do not need to be modified to run this
#      example. If you want to modify the configuration in any of these files,
#      copy it to this directory and modify as needed.
#
#  $(EXAMPLES_ROOTDIR)/ti/sdo/ce/examples/apps/speech1_copy/
#      app.c
#      main_native.c
#
#      These are the same source files used to build the XDC configurable
#      version of this app. They do not need to be modified for the run-time
#      configuration example.
#
#  $(CURDIR)/
#      app_config.c
#      evm3530_config.c
#
#      The file, app_config.c, contains algorithm and engine tables needed
#      by the app. The file, evm3530_config.c, contains platform specific
#      configuration.
#
#  The vpath variable below sets the search path for the source files.
#
APP.srcs =                      \
	rtcfg.c                 \
	rtcfg_wince.c           \
	rtcfg_dman3.c           \
	rtcfg_rman.c            \
        app_config.c            \
        evm3530_config.c        \
        app.c                   \
        main_native.c

APP.objs = $(addprefix bin/$(PLAT)/$(PROFILE)/, \
    $(patsubst %.c,%.o$(SUFFIX),$(APP.srcs)))

#
#  The vpath variable lets us maintain some of the same sources for both XDC
#  build and gmake build, and use default run-time configuration files.
#
CE_APPS_DIR ?= $(EXAMPLES_ROOTDIR)/ti/sdo/ce/examples/apps
vpath %.c $(CE_APPS_DIR)/speech1_copy $(CE_REPO)/ti/sdo/ce/utils/rtcfg

LIBS = \
	"$(EXAMPLES_ROOTDIR)/ti/xdais/dm/examples/sphdec1_copy/lib/$(PROFILE)/sphdec1_copy.av4TCE" \
	"$(EXAMPLES_ROOTDIR)/ti/xdais/dm/examples/sphenc1_copy/lib/$(PROFILE)/sphenc1_copy.av4TCE"


#
#  ======== compute build goals from DEVICES and PROGRAMS ========
#  Don't attempt to build unless DEVICES = OMAP3530, PROGRAMS = APP_LOCAL,
#  and GPPOS is WINCE.
#
ifneq (,$(findstring OMAP3530,$(DEVICES)))
ifneq (,$(findstring APP_LOCAL,$(PROGRAMS)))
ifneq (,$(findstring WINCE,$(GPPOS)))
GOALS := $(GOALS) OMAP3530_APP_LOCAL
endif
endif
endif

ifeq (,$(GOALS))
GOALS = nothing
endif

#
#  ======== make commands ========
#
all:
	$(MAKE) $(GOALS)

OMAP3530_APP_LOCAL:
	@$(ECHO) "#"
	@$(ECHO) "# Making $@ ..."
	@$(MAKE) PLAT=ti_platforms_evm3530 \
            PROFILE=debug \
            bin/ti_platforms_evm3530/debug/speech1_copy_wince.exe
	@$(MAKE) PLAT=ti_platforms_evm3530 \
            PROFILE=release \
            bin/ti_platforms_evm3530/release/speech1_copy_wince.exe


nothing:
	@$(ECHO) "Nothing to build for the given devices and programs"
	@$(ECHO) "    DEVICES=\"$(DEVICES)\""
	@$(ECHO) "    PROGRAMS=\"$(PROGRAMS)\""

#
#  ======== build rules ========
#
bin/$(PLAT)/$(PROFILE)/%.exe: $(APP.objs)
	@$(ECHO) "#"
	@$(ECHO) "# Making $@ ..."
	$(LNK) -out:$@ $^ $(LOPTS) $(addprefix -libpath:,$(REPO_PATH)) -map:$@.map -pdb:$@.pdb $(CE_LIBS) $(FC_LIBS) $(LIBS)

.SECONDARY:
bin/$(PLAT)/$(PROFILE)/%.o$(SUFFIX): %.h
bin/$(PLAT)/$(PROFILE)/%.o$(SUFFIX): %.c
	@$(ECHO) "#"
	@$(ECHO) "# Making $@ ..."
	$(CC) $(DEFS) $(INCS) /Fo$@ $<

#
#  ======== clean ========
#
clean::
	$(RMDIR) bin
#
#  @(#) ti.sdo.ce.examples.apps.speech1_copy; 1, 0, 0,263; 12-2-2010 21:20:25; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

#

