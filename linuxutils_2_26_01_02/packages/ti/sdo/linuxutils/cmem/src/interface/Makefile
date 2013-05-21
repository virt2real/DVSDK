#
# Copyright (c) 2010, Texas Instruments Incorporated
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# *  Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
# *  Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# *  Neither the name of Texas Instruments Incorporated nor the names of
#    its contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

ROOTDIR = ../..
TARGET = cmem

include $(ROOTDIR)/Rules.make

CC = $(MVTOOL_PREFIX)gcc
AR = $(MVTOOL_PREFIX)ar

CCuC = $(UCTOOL_PREFIX)gcc
ARuC = $(UCTOOL_PREFIX)ar

INCLUDEDIR = $(ROOTDIR)/include
LIBDIR	   = $(ROOTDIR)/lib

C_FLAGS += -I. -Wall

COMP.c  = $(CC) $(C_FLAGS) $(CPP_FLAGS) -c
AR.c	= $(AR) rc

COMP.uC = $(CCuC) $(C_FLAGS) $(CPP_FLAGS) -c
AR.uC	= $(ARuC) rc

GLIBCTARGETS = $(LIBDIR)/$(TARGET).a470MV $(LIBDIR)/$(TARGET)d.a470MV
UCLIBCTARGETS = $(LIBDIR)/$(TARGET).a470uC $(LIBDIR)/$(TARGET)d.a470uC

DBGTARGETS = $(LIBDIR)/$(TARGET)d.a470MV $(LIBDIR)/$(TARGET)d.a470uC
RELTARGETS = $(LIBDIR)/$(TARGET).a470MV $(LIBDIR)/$(TARGET).a470uC

DBGCFLAGS = -g -D__DEBUG
RELCFLAGS = -O2

SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)

TARGETHEADERS = $(addprefix $(INCLUDEDIR)/, $(HEADERS))

DBGOBJFILES = $(SOURCES:%.c=debug/%.o470MV) $(SOURCES:%.c=debug/%.o470uC)
RELOBJFILES = $(SOURCES:%.c=release/%.o470MV) $(SOURCES:%.c=release/%.o470uC)

.PHONY: clean debug release install all glibc uclibc

all: debug release

install:

release: $(RELTARGETS) $(TARGETHEADERS)

debug: $(DBGTARGETS) $(TARGETHEADERS)

glibc: $(GLIBCTARGETS)

uclibc: $(UCLIBCTARGETS)

$(filter %.a470MV,$(RELTARGETS)): $(filter %.o470MV,$(RELOBJFILES))
	@mkdir -p $(ROOTDIR)/lib
	$(AR.c) $@ $^

$(filter %.a470uC,$(RELTARGETS)): $(filter %.o470uC,$(RELOBJFILES))
	@mkdir -p $(ROOTDIR)/lib
	$(AR.uC) $@ $^

$(filter %.a470MV,$(DBGTARGETS)): $(filter %.o470MV,$(DBGOBJFILES))
	@mkdir -p $(ROOTDIR)/lib
	$(AR.c) $@ $^

$(filter %.a470uC,$(DBGTARGETS)): $(filter %.o470uC,$(DBGOBJFILES))
	@mkdir -p $(ROOTDIR)/lib
	$(AR.uC) $@ $^

$(filter %.o470MV,$(RELOBJFILES)): release/%.o470MV: %.c $(HEADERS)
	@mkdir -p release
	$(COMP.c) $(RELCFLAGS) -o $@ $<

$(filter %.o470uC,$(RELOBJFILES)): release/%.o470uC: %.c $(HEADERS)
	@mkdir -p release
	$(COMP.uC) $(RELCFLAGS) -o $@ $<

$(filter %.o470MV,$(DBGOBJFILES)): debug/%.o470MV: %.c $(HEADERS)
	@mkdir -p debug
	$(COMP.c) $(DBGCFLAGS) -o $@ $<

$(filter %.o470uC,$(DBGOBJFILES)): debug/%.o470uC: %.c $(HEADERS)
	@mkdir -p debug
	$(COMP.uC) $(DBGCFLAGS) -o $@ $<

$(TARGETHEADERS): $(HEADERS)
	@echo Installing headers...
	@install -d $(INCLUDEDIR)
	@install $< $@

clean:
	-rm -rf release debug *~
	-rm -f $(DBGTARGETS) $(RELTARGETS)
#
#  @(#) ti.sdo.linuxutils.cmem; 2, 2, 0,142; 11-30-2010 18:31:30; /db/atree/library/trees/linuxutils/linuxutils-j02x/src/ xlibrary

#

