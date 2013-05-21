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
#  ======== makefile =======
#  GNUmake-based makefile
#

# This file describes the build for a generic Linux application that
# happens to use Codec Engine. This makefile has special sections to
# accomodate inclusion of the codec engine, while the rest is standard.
# Codec Engine-specific additions are marked with the [CE] tag.

# [CE] define EXAMPLES_ROOTDIR to point to root of <CE/examples> directory
EXAMPLES_ROOTDIR := $(CURDIR)/../../../../../../../..

# [CE] include the file that defines paths to XDC packages and XDC tools
include $(EXAMPLES_ROOTDIR)/xdcpaths.mak

# [CE] add the examples repository to the package path.
# This is necessary because this application's configuration uses the codecs
# in the examples repository
XDC_PATH := $(EXAMPLES_ROOTDIR);$(XDC_PATH)

# The compiler path and name are read from xdcpaths.mak above
CGTOOLS = $(CGTOOLS_V5T)

# compiler
CC = $(CGTOOLS)/$(CC_V5T)

# [CE] Configuro settings.  CONFIGPKG is the basename of your application's
# config script
CONFIGPKG = local
CONFIG_BLD := ./config.bld

# [CE] Name the xdc platform
XDCPLATFORM = ti.platforms.evmDM365

# [CE] configuro-generated files
COMPILER_FILE = $(CONFIGPKG)/compiler.opt
LINKER_FILE = $(CONFIGPKG)/linker.cmd

# [CE] The path to the configuro utility
CONFIGURO = XDCPATH="$(XDC_PATH)" XDCARGS=$(XDCARGS) \
        $(XDC_INSTALL_DIR)/xs xdc.tools.configuro

# [CE] Augment the standard $(CPPFLAGS) variable, adding the
# Configuro-generated compiler file.
CPPFLAGS +=  $(shell cat $(COMPILER_FILE)) -g -Wall -Os

# final executable
all: app.out

# [CE] The generated linker and compiler files depend on the generated
# config package
$(LINKER_FILE) $(COMPILER_FILE) : $(CONFIGPKG)

# [CE] The generated config package depends on the config script
# Only need to set platform (-p option).  The target (-t) and codegen (-c) are
# set in config.bld (-b)
$(CONFIGPKG) : $(CONFIGPKG).cfg
	$(CONFIGURO) -o $(CONFIGPKG) \
		-p $(XDCPLATFORM) -b $(CONFIG_BLD) $<

# These 2 sneaky vpath commands tell gmake "if you don't find the file
# in this directory, try ../.. before giving up.  For more info, see
# http://www.gnu.org/software/make/manual/make.html#Selective-Search
#
# This lets us maintain one set of sources for many different devices.
vpath %.c ../..
vpath %.cfg ../..

# "normal" makefile settings and rules follow, with some additions for CE
# This app consists of the main, codec-engine unrelated main.c file, and
# the codec-engine-using app.c file.
%.o : %.c $(COMPILER_FILE)
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<


# app.out, in addition to its standard stuff, must specify the
# auto-generated $(LINKER_FILE)
app.out: app.o main_native.o $(LINKER_FILE)
	$(CC) -o $@ $^ -lpthread

# clean rule
clean:
	rm -rf app.out *.o $(CONFIGPKG)
#
#  @(#) ti.sdo.ce.examples.apps.video_copy; 1, 0, 0,77; 12-2-2010 21:21:30; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

#

