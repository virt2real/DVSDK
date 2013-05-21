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
TARGET = $(notdir $(shell pwd))

include $(ROOTDIR)/Rules.make

CC = $(MVTOOL_PREFIX)gcc

CCuC = $(UCTOOL_PREFIX)gcc

C_FLAGS += -Wall -I$(ROOTDIR)/include

COMP.c = $(CC) $(C_FLAGS) $(CPP_FLAGS) -c
LINK.c = $(CC) $(LD_FLAGS)

COMP.uC = $(CCuC) $(C_FLAGS) $(CPP_FLAGS) -c
LINK.uC = $(CCuC) $(LD_FLAGS)

DBGTARGETS = debug/$(TARGET)d debug/$(TARGET)d.x470uC
RELTARGETS = release/$(TARGET) release/$(TARGET).x470uC

DBGCFLAGS = -g -D__DEBUG
RELCFLAGS = -O2

DBGLDFLAGS = $(ROOTDIR)/lib/cmemd.a470MV $(ROOTDIR)/lib/cmemd.a470uC
RELLDFLAGS = $(ROOTDIR)/lib/cmem.a470MV $(ROOTDIR)/lib/cmem.a470uC

SOURCES = $(wildcard *.c)

DBGOBJFILES = $(SOURCES:%.c=debug/%.o470MV) $(SOURCES:%.c=debug/%.o470uC)
RELOBJFILES = $(SOURCES:%.c=release/%.o470MV) $(SOURCES:%.c=release/%.o470uC)

.PHONY: clean debug release install

all: debug release

install:
	install -d $(EXEC_DIR)
	install $(RELTARGETS) $(EXEC_DIR)
	install $(DBGTARGETS) $(EXEC_DIR)

release: $(RELTARGETS)

debug: $(DBGTARGETS)

$(filter %translate,$(RELTARGETS)): $(filter %.o470MV,$(RELOBJFILES)) \
    $(filter %.a470MV,$(RELLDFLAGS))
	$(LINK.c) -o $@ $^

$(filter %.x470uC,$(RELTARGETS)): $(filter %.o470uC,$(RELOBJFILES)) \
    $(filter %.a470uC,$(RELLDFLAGS))
	$(LINK.uC) -o $@ $^

$(filter %translated,$(DBGTARGETS)): $(filter %.o470MV,$(DBGOBJFILES)) \
    $(filter %.a470MV,$(DBGLDFLAGS))
	$(LINK.c) -o $@ $^

$(filter %.x470uC,$(DBGTARGETS)): $(filter %.o470uC,$(DBGOBJFILES)) \
    $(filter %.a470uC,$(DBGLDFLAGS))
	$(LINK.uC) -o $@ $^

$(filter %.o470MV,$(RELOBJFILES)): release/%.o470MV: %.c
	@mkdir -p release
	$(COMP.c) $(RELCFLAGS) -o $@ $<

$(filter %.o470uC,$(RELOBJFILES)): release/%.o470uC: %.c
	@mkdir -p release
	$(COMP.uC) $(RELCFLAGS) -o $@ $<

$(filter %.o470MV,$(DBGOBJFILES)): debug/%.o470MV: %.c
	@mkdir -p debug
	$(COMP.c) $(DBGCFLAGS) -o $@ $<

$(filter %.o470uC,$(DBGOBJFILES)): debug/%.o470uC: %.c
	@mkdir -p debug
	$(COMP.uC) $(DBGCFLAGS) -o $@ $<

clean:
	-rm -rf release debug *~
	-rm -f $(DBGTARGETS) $(RELTARGETS)
#
#  @(#) ti.sdo.linuxutils.cmem; 2, 2, 0,142; 11-30-2010 18:31:30; /db/atree/library/trees/linuxutils/linuxutils-j02x/src/ xlibrary

#

