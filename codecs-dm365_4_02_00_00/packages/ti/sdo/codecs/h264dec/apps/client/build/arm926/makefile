ROOTDIR = ./
TARGET = h264vdec

REL_LIB = $(TARGET)-r.a
REL_BIN = $(TARGET)-r

ALG_LIB1 = ../../../../lib/h264vdec_ti_arm926.a
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
CONFIGPKG = h264vdec_ti_dm365testapp_linux

#Path to Configuro utility
CONFIGURO = XDCPATH="$(XDC_PATH)" $(XDC_INSTALL_DIR)/xs xdc.tools.configuro

C_FLAGS += -g -o3 -D"LOW_LATENCY_FEATURE" -D"_ARM926"  -D"ON_LINUX" -D"DM365_IPC_INTC_ENABLE" -U"ENABLE_CACHE" -U"WORK_ON_SIMULATOR" -D"FLD_API" -U"TEST_RESET"

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

OBJECTS = buffermanager.o crc.o h264vdec.o seperateCbCr.o testappconfigparser.o TestAppDecoder_ih264_arm926.o TestAppXDMResetDecoder_ih264_arm926.o alg_malloc.o alg_create.o
OBJECTS1 = ./release/buffermanager.o ./release/crc.o ./release/h264vdec.o ./release/seperateCbCr.o ./release/testappconfigparser.o 
OBJECTS1 +=	./release/TestAppDecoder_ih264_arm926.o  ./release/TestAppXDMResetDecoder_ih264_arm926.o ./release/alg_malloc.o ./release/alg_create.o

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
buffermanager_mi.o:
	$(CC) $(C_FLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o release/buffermanager_mi.o  ../../test/src/buffermanager_mi.c 
buffermanager.o:
	$(CC) $(C_FLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o release/buffermanager.o  ../../test/src/buffermanager.c 
crc.o:
	$(CC) $(C_FLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o release/crc.o  ../../test/src/crc.c 
h264vdec.o:
	$(CC) $(C_FLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o release/h264vdec.o  ../../test/src/h264vdec.c 
seperateCbCr.o:
	$(CC) $(C_FLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o release/seperateCbCr.o  ../../test/src/seperateCbCr.c 
testappconfigparser.o:
	$(CC) $(C_FLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o release/testappconfigparser.o  ../../test/src/testappconfigparser.c 
testappbaseparamdecoder_ih264_arm926.o:
	$(CC) $(C_FLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o release/testappbaseparamdecoder_ih264_arm926.o  ../../test/src/testappbaseparamdecoder_ih264_arm926.c 
TestAppDumpFailFrm_ih264_arm926.o:
	$(CC) $(C_FLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o release/TestAppDumpFailFrm_ih264_arm926.o  ../../test/src/TestAppDumpFailFrm_ih264_arm926.c 
TestAppXDMResetDecoder_ih264_arm926.o:
	$(CC) $(C_FLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o release/TestAppXDMResetDecoder_ih264_arm926.o  ../../test/src/TestAppXDMResetDecoder_ih264_arm926.c 
TestAppDecoder_ih264_arm926.o:
	$(CC) $(C_FLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o release/TestAppDecoder_ih264_arm926.o  ../../test/src/TestAppDecoder_ih264_arm926.c 
TestMiDecoder_ih264_arm926.o:
	$(CC) $(C_FLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o release/TestMiDecoder_ih264_arm926.o  ../../test/src/TestMiDecoder_ih264_arm926.c 
testappfrmsizedecoder_ih264_arm926.o:
	$(CC) $(C_FLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o release/testappfrmsizedecoder_ih264_arm926.o  ../../test/src/testappfrmsizedecoder_ih264_arm926.c 

$(REL_BIN): $(XDC_LINKER_FILE) $(OBJECTS) 
	$(LN) -o $@ $(OBJECTS1) $(LD_LIBS) $(XDC_LINKER_FILE)

clean::
	-rm -rf release
	-rm -rf $(REL_LIB)
	-rm -rf $(REL_BIN)
	-rm -rf $(CONFIGPKG)

copy:
	sum h264vdec-r
	cp h264vdec-r /home/dvsdkmmc/workdir/filesys_dm365/DM365Worspace/h264Decoder/regression
