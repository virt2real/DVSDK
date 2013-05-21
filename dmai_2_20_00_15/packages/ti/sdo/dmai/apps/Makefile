# --COPYRIGHT--,BSD
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
# --/COPYRIGHT--

SUBDIRS = $(sort $(dir $(wildcard */)))
CLEANSUBDIRS = $(addsuffix .clean, $(SUBDIRS))
INSTALLSUBDIRS = $(addsuffix .install, $(SUBDIRS))

ifeq ($(VERBOSE), true)
	MAKE := $(MAKE)
else
	MAKE := $(MAKE) --no-print-directory
endif

.PHONY: install clean $(SUBDIRS)

all:	$(SUBDIRS)

$(SUBDIRS):
	@echo
	@echo Executing make in subdirectory $(basename $@)...
	@$(MAKE) -C $(basename $@) all

install: $(INSTALLSUBDIRS)

$(INSTALLSUBDIRS):
	@echo
	@echo Executing make install in subdirectory $(basename $@)...
	@$(MAKE) -C $(basename $@) install

clean:	$(CLEANSUBDIRS)

$(CLEANSUBDIRS):
	@echo Executing make clean in subdirectory $(basename $@)...
	@$(MAKE) -C $(basename $@) clean
