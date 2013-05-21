ROOTDIR = ./
TARGET = h264venc
REL_LIB = $(TARGET)-r.a
REL_BIN = $(TARGET)-r

ALG_LIB1 = ../../../../lib/h264venc_ti_arm926.a
ALG_LIB2 = ../../../../lib/h264v_ti_dma_dm365.a 

include $(ROOTDIR)/rules.make

CGTOOLS = $(MVTOOL_DIR)
CEPATH = $(CE_INSTALL_DIR)

XDC_PATH = $(XDAIS_INSTALL_DIR)/packages;$(LINUXUTILS_INSTALL_DIR)/packages;$(FC_INSTALL_DIR)/packages;$(FC_INSTALL_DIR)/examples;$(CEPATH)/packages;$(CEPATH)/cetools/packages;$(LINUXUTILS_INSTALL_DIR)/packages;

#Configuro Changes
#Base name of app's config script - This needs to externally specified while
#building DVTB
ifeq ($(COMPILER),mvl)
XDCTARGET = gnu.targets.MVArm9
else
ifeq ($(COMPILER),cst)
XDCTARGET = gnu.targets.arm.GCArmv5T
else
$(error COMPILER option not set correctly: $(COMPILER))
endif
endif
XDCPLATFORM = ti.platforms.evmDM365

#Configuro generated files
XDC_COMPILER_FILE = $(CONFIGPKG)/compiler.opt
XDC_LINKER_FILE = $(CONFIGPKG)/linker.cmd
CONFIGPKG = h264venc_ti_dm365testapp_linux

#Path to Configuro utility
CONFIGURO = XDCPATH="$(XDC_PATH)" $(XDC_INSTALL_DIR)/xs xdc.tools.configuro

C_FLAGS += -g -D"LOW_LATENCY_FEATURE" -D"_ARM926" -D"ON_LINUX" -D"H264ENC_EDMA" -D"_DEBUG" -D"DM365_IPC_INTC_ENABLE" -U"ENABLE_CACHE" -D"SEI_USERDATA_INSERTION" -U"BASE_PARAMS" -D"DEVICE_ID_CHECK" -U"PASS_SAD_MV_APPL" -U"ENABLE_ARM926_TCM" -D"ENABLE_ROI" -D"SIMPLE_TWO_PASS" -U"PROFILE_ONLINUX" -D"MEGA_PIX"


INCLUDES += -I../../test/inc -I../../../inc -I../../../../H264_dma/inc -I../../../../csl/arm/include -I../../../../csl/kld/include \
		 -I $(LINUXKERNEL_INSTALL_DIR)/include -I $(XDAIS_INSTALL_DIR)/packages/ti/xdais/include

LD_LIBS += -lpthread $(EDITLINE_LIB)  -lstdc++ $(ALG_LIB1) $(ALG_LIB2) 

AR_FLAGS += -r 

CC = $(MVTOOL_PREFIX)gcc $(INCLUDES) $(C_FLAGS) $(shell cat $(XDC_COMPILER_FILE)) -c
AR = $(MVTOOL_PREFIX)ar
LN = $(MVTOOL_PREFIX)gcc

REL_FLAGS =

SOURCES = $(wildcard *.c)

REL_OBJ = $(SOURCES:%.c=release/%.o)

OBJECTS = alg_control.o alg_create.o alg_malloc.o h264encoderapp.o h264venc.o #hdvicp_framework.o 
OBJECTS1 = ./release/alg_control.o ./release/alg_create.o ./release/alg_malloc.o ./release/h264encoderapp.o ./release/h264venc.o #./release/hdvicp_framework.o

all:	$(REL_BIN)

#Dependency on Config package
$(XDC_COMPILER_FILE) $(XDC_LINKER_FILE) : $(CONFIGPKG)

#Config package dependency
ifeq ($(COMPILER),mvl)
$(CONFIGPKG) : $(CONFIGPKG).cfg
	@mkdir -p release
	$(CONFIGURO) -c $(MVTOOL_DIR) -o $(CONFIGPKG) -t $(XDCTARGET) -p $(XDCPLATFORM) $(CONFIGPKG).cfg
else
ifeq ($(COMPILER),cst)
$(CONFIGPKG) : $(CONFIGPKG).cfg
	@mkdir -p release
	@$(CONFIGURO) -c $(MVTOOL_DIR) -o $(CONFIGPKG) -t $(XDCTARGET) -p $(XDCPLATFORM) -b ./config.bld $(CONFIGPKG).cfg
else
$(error COMPILER option not set correctly: $(COMPILER))
endif
endif	
$(REL_OBJ):	release/%.o: %.c $(XDC_COMPILER_FILE)
	@mkdir -p release
	$(CC) $(C_FLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o $@ $<

alg_control.o:
	$(CC) $(C_FLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o release/alg_control.o  ../../test/src/alg_control.c
alg_create.o:
	$(CC) $(C_FLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o release/alg_create.o  ../../test/src/alg_create.c 
alg_malloc.o:
	$(CC) $(C_FLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o release/alg_malloc.o  ../../test/src/alg_malloc.c 
h264encoderapp.o:
	$(CC) $(C_FLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o release/h264encoderapp.o  ../../test/src/h264encoderapp.c 
#h264encoderapp.o:
#	$(CC) $(C_FLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o release/h264encoderapp.o  ../../test/src/h264encoderapp_base.c 
hdvicp_framework.o:
	$(CC) $(C_FLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o release/hdvicp_framework.o  ../../test/src/hdvicp_framework.c 
h264venc.o:
	$(CC) $(C_FLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o release/h264venc.o  ../../test/src/h264venc.c 
testapp_arm926intc.o:
	$(CC) $(C_FLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o release/testapp_arm926intc.o  ../../test/src/testapp_arm926intc.c 

$(REL_BIN): $(XDC_LINKER_FILE) $(OBJECTS) 
	$(LN) -o $@ $(OBJECTS1) $(LD_LIBS) $(XDC_LINKER_FILE)

clean::
	-rm -rf release
	-rm -rf $(REL_LIB)
	-rm -rf $(REL_BIN)
	-rm -rf $(CONFIGPKG)

copy:
	cp h264venc-r /opt/yashwant/target/root/h264linux/h264_encoder/client/build/arm926/
