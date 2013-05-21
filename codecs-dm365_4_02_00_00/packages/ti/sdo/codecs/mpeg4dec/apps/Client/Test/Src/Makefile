ROOTDIR = ../../../../
TARGET = mp4dec

REL_LIB = $(TARGET)-r.a
REL_BIN = $(TARGET)-r

ALG_LIB1 = ../../../Lib/libmp4dec.a
ALG_LIB2 = ../../../Lib/libdm355mm.a 
ALG_LIB3 =$(FC_INSTALL_DIR)/packages/ti/sdo/fc/memutils/lib/release/memutils.a470MV 
ALG_LIB4 =  $(FC_INSTALL_DIR)/packages/ti/sdo/fc/vicpsync/lib/release/vicpsync.a470MV
include $(ROOTDIR)/Rules.make

CGTOOLS = $(MVTOOL_DIR)
XDAIS_INSTALL_DIR = $(FC_INSTALL_DIR)/fctools
EDMA3_LLD_ROOT = $(FC_INSTALL_DIR)/fctools

#XDC_PATH = $(FC_LINUXUTILS_INSTALL_DIR)/packages;$(XDAIS_INSTALL_DIR)/packages;$(FC_INSTALL_DIR)/packages;$(FC_INSTALL_DIR)/examples;$(EDMA3_LLD_ROOT)/packages;
XDC_PATH = $(XDAIS_INSTALL_DIR)/packages;$(FC_INSTALL_DIR)/packages;$(FC_INSTALL_DIR)/examples;$(EDMA3_LLD_ROOT)/packages;

#Configuro Changes
#Base name of app's config script - This needs to externally specified while
#building DVTB
XDCTARGET = gnu.targets.MVArm9
#XDCPLATFORM = ti.platforms.evmDM355
XDCPLATFORM = ti.platforms.evmDM365

#Configuro generated files
XDC_COMPILER_FILE = $(CONFIGPKG)/compiler.opt
XDC_LINKER_FILE = $(CONFIGPKG)/linker.cmd
CONFIGPKG = mp4vdecTestApp

#Path to Configuro utility
CONFIGURO = XDCPATH="$(XDC_PATH)" $(XDC_INSTALL_DIR)/xs xdc.tools.configuro

C_FLAGS += -Wall -DDM355  -DLINUX -UENABLE_IDMA3 -Dfar="" 

INCLUDES += -I ../Inc -I ../../../Inc  -I $(LINUXKERNEL_INSTALL_DIR)/include -I $(XDAIS_INSTALL_DIR)/packages -I $(XDAIS_INSTALL_DIR)/packages/ti/xdais/include -I ./ -I ../../../../include

LD_LIBS += -lpthread $(EDITLINE_LIB) -lcurses -lstdc++ $(ALG_LIB1)  $(ALG_LIB3) $(ALG_LIB4) 
AR_FLAGS += -r 

CC = $(MVTOOL_PREFIX)gcc $(INCLUDES) $(C_FLAGS) $(shell cat $(XDC_COMPILER_FILE)) -c
AR = $(MVTOOL_PREFIX)ar
LN = $(MVTOOL_PREFIX)gcc

REL_FLAGS =

SOURCES = $(wildcard *.c)

REL_OBJ = $(SOURCES:%.c=release/%.o)

all:	$(REL_LIB) $(REL_BIN)

#Dependency on Config package
$(XDC_COMPILER_FILE) $(XDC_LINKER_FILE) : $(CONFIGPKG)

#Config package dependency
$(CONFIGPKG) : $(CONFIGPKG).cfg
	$(CONFIGURO) -c $(MVTOOL_DIR) -o $(CONFIGPKG) -t $(XDCTARGET) -p $(XDCPLATFORM) $(CONFIGPKG).cfg
	
$(REL_LIB): $(REL_OBJ)
	$(AR) $(AR_FLAGS) $(REL_LIB) $(REL_OBJ)

$(REL_OBJ):	release/%.o: %.c $(XDC_COMPILER_FILE)
	@mkdir -p release
	$(CC) $(C_FLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o $@ $<

$(REL_BIN):	$(REL_LIB) $(XDC_LINKER_FILE)
	$(LN) -o $@ $^ $(LD_LIBS) $(REL_LIB)

clean::
	-rm -rf release
	-rm -rf $(REL_LIB)
	-rm -rf $(REL_BIN)
	-rm -rf $(CONFIGPKG)
