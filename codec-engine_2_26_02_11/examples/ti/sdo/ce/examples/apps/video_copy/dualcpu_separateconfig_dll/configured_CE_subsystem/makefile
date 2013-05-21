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

#
#  ======== makefile =======
#  GNUmake-based makefile for linuxonly speech sample app.
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
CONFIGPKG = ceapp
CONFIG_BLD := $(EXAMPLES_ROOTDIR)/config.bld

# [CE] Name the xdc target and platform
XDCTARGET = $(CGTARGET)
XDCPLATFORM = ti.platforms.evmDM6446

# [CE] configuro-generated files
COMPILER_FILE = $(CONFIGPKG)/compiler.opt
LINKER_FILE = $(CONFIGPKG)/linker.cmd

# [CE] The path to the configuro utility
CONFIGURO = XDCPATH="$(XDC_PATH)" $(XDC_INSTALL_DIR)/xs xdc.tools.configuro

# [CE] Augment the standard $(CPPFLAGS) variable, adding the
# Configuro-generated compiler file.
CPPFLAGS +=  $(shell cat $(COMPILER_FILE)) -g -Wall -Os

all: configured_CE_subsystem.so

# [CE] The generated linker and compiler files depend on the generated
# config package
$(LINKER_FILE) $(COMPILER_FILE) : $(CONFIGPKG)

# [CE] The generated config package depends on the 2 config scripts
$(CONFIGPKG) : $(CONFIGPKG).cfg
	$(CONFIGURO) -c $(CGTOOLS) -o $(CONFIGPKG) \
		-t $(XDCTARGET) -p $(XDCPLATFORM) \
		-b $(CONFIG_BLD) -Dplatname=$(XDCPLATFORM) $(CONFIGPKG).cfg

# "normal" makefile settings and rules follow, with some additions for CE
# This app consists of the main, codec-engine unrelated main.c file, and
# the codec-engine-using app.c file.
%.o : %.c $(COMPILER_FILE)
	$(CC) -c -fPIC $(CPPFLAGS) $(CFLAGS) -o $@ $<


# [CE] link configured CE-using app and all CE libraries it requires (but no others)
# into a shared library, configured_CE_subsystem.so which
# includes .o's and .libs listed in the configuration-generated $(LINKER_FILE)
configured_CE_subsystem.so: ceapp.o $(LINKER_FILE)
	$(CC) -fPIC -shared -o $@ $^ 

# clean rule
clean:
	rm -rf *.o *.so $(CONFIGPKG)
#
#  @(#) ti.sdo.ce.examples.apps.video_copy; 1, 0, 0,77; 12-2-2010 21:21:31; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

#

