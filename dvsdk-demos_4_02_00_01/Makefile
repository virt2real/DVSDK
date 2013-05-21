#
# Makefile for making the DVSDK demos
#
# Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
# 
# 
#  Redistribution and use in source and binary forms, with or without 
#  modification, are permitted provided that the following conditions 
#  are met:
#
#    Redistributions of source code must retain the above copyright 
#    notice, this list of conditions and the following disclaimer.
#
#    Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the 
#    documentation and/or other materials provided with the   
#    distribution.
#
#    Neither the name of Texas Instruments Incorporated nor the names of
#    its contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
#  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
#  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
#  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
#  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
#  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

ROOTDIR = ..
include $(ROOTDIR)/Rules.make

SUBDIRS = $(filter-out data/ packages/ patches/ qtInterface/, $(sort $(dir $(wildcard */))))

CLEAN_SUBDIRS = $(addsuffix .clean, $(SUBDIRS))
INSTALL_SUBDIRS = $(addsuffix .install, $(SUBDIRS))

.PHONY: install clean $(SUBDIRS) $(INSTALL_SUBDIRS) $(CLEAN_SUBDIRS) dm6467 dm6446 dm355 omap3530 dm365 dm368 dm3730

all:	$(if $(wildcard dm6467), dm6467)	\
	$(if $(wildcard dm6446), dm6446)	\
	$(if $(wildcard dm365), dm365)		\
	$(if $(wildcard omap3530), omap3530)	\
        $(if $(wildcard dm355), dm355)		\
	$(if $(wildcard dm3730), dm3730)	\
	$(if $(wildcard dm368), dm368)

simplewidget:

dm6467:
	@echo
	@echo Building simplewidget..
	$(MAKE) -C packages/ti/sdo/simplewidget dm6467
	@echo Making all in subdirectory $@...
	$(MAKE) -C dm6467

dm6446:
	@echo
	@echo Building simplewidget..
	$(MAKE) -C packages/ti/sdo/simplewidget dm6446
	@echo Making all in subdirectory $@...
	$(MAKE) -C dm6446

dm365:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C dm365

dm355:
	@echo
	@echo Building simplewidget..
	$(MAKE) -C packages/ti/sdo/simplewidget dm355
	@echo Making all in subdirectory $@...
	$(MAKE) -C dm355

omap3530:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C omap3530

dm3730:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C dm3730

dm368:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C dm368

install: $(INSTALL_SUBDIRS)

$(INSTALL_SUBDIRS):
	@echo
	@echo Executing make install in subdirectory $(basename $@)...
	@cd $(basename $@) ; $(MAKE) install

clean:	$(CLEAN_SUBDIRS) $(if $(wildcard packages), simplewidget_clean)

simplewidget_clean:
	@make -C packages/ti/sdo/simplewidget clean

$(CLEAN_SUBDIRS):
	@cd $(basename $@) ; $(MAKE) clean
