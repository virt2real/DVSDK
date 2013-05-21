#Environment variable settings
XDAIS_INSTALL_DIR = $(FC_INSTALL_DIR)/fctools

#XDC related settings
CONFIG = mpeg2venc_ti_dm365testapp
XDCTARGET = ti.targets.arm.Arm9t
#XDCPLATFORM = ti.platforms.evmDM355
XDCPLATFORM = ti.platforms.simDM365
XDCPATH = ^;$(XDAIS_INSTALL_DIR)/packages;$(FC_INSTALL_DIR)/packages/;$(FC_INSTALL_DIR)/examples;$(BIOS_INSTALL_DIR)/packages;

export XDCPATH
export XDAIS_INSTALL_DIR

#Makefile variable settings for project compilation
CGTOOLS = D:/CCStudio_v3.3/tms470/cgtools
CCS_INCLUDES = D:/CCStudio_v3.3/tms470/cgtools/include

CC = $(CGTOOLS)/bin/cl470
LNK = $(CGTOOLS)/bin/lnk470
RTS = $(CGTOOLS)/lib/rts32earm9.lib

#Compilation related options

CFLAGS  = -g -oi200 -o0 -mc -mf -mv5e --abi=ti_arm9_abi --code_state=32 --endian=little 
CFLAGS_1 = -g -oi200 -mc -mf -mv5e --abi=ti_arm9_abi --code_state=32 --endian=little 
CFLAGS_XDC = -@./$(CONFIG)/compiler.opt
INCLUDES = -I../../Test/inc -I../../../inc -I../../../../dma/inc -I../../../../csl/arm/include -I../../../../csl/drv/mmcsd0/include -I../../../../csl/drv/mmcsd1/include -I ../../../../csl/drv/ms/include -I../../../../csl/kld/include
INCLUDES += -I$(FC_INSTALL_DIR)/packages
INCLUDES += -I$(FC_INSTALL_DIR)/fctools/packages
INCLUDES += -I$(CCS_INCLUDES)
INCLUDES += -I../../../Src/Inc
INCLUDES += -I../../../Inc
INCLUDES += -I../../../Client/Test/Inc
DEFS = -D"_ARM926" -D"DM360_IPC_INTC_ENABLE" -D"ARM926_ENABLE_CACHE" -u"DEVICE_ID_CHECK"
OUTFILE =
LIBS = -c -w -x -l$(RTS) -l"../../../lib/dma_ti_dm510.lib" -l"../../../lib/mpeg2venc_ti_arm926.lib"
CMDFILE = -l=../arm926/cmd/mpeg2venc_ti_arm926.cmd

OBJECTS =  hdvicp_framework.obj mpeg2venc_ti_formatconvt.obj mpeg2venc_ti_api.obj testapp_inthandler.obj  myLinuxutils.obj  \
	LockMP.obj testapp_intvecs.obj testapp_mmutable.obj testapp_arm926intc.obj mpeg2venc_ti_arm926testapp.obj testapp_idma.obj

#dummyTest.obj ires_algorithm.obj


all: testAppObj
	$(LNK) $(LIBS) $(CMDFILE) $(OBJECTS) ./$(CONFIG)/linker.cmd $(RTS) -o ./out/mpeg2venc_ti_arm926.out -m mpeg2venc_ti_dm365testapp.map
	del *.obj
  
testAppObj: $(CONFIG)/linker.cmd $(CONFIG)/compiler.opt $(OBJECTS)

#alg_control.obj:
#	$(CC)     $(CFLAGS_XDC) $(CFLAGS) $(OUTFILE)  $(INCLUDES) $(DEFS)  #../../Test/Src/alg_control.c
#alg_create.obj:
#	$(CC)     $(CFLAGS_XDC) $(CFLAGS) $(OUTFILE)  $(INCLUDES) $(DEFS)  #../../Test/Src/alg_create.c 
#alg_malloc.obj:
#	$(CC)     $(CFLAGS_XDC) $(CFLAGS) $(OUTFILE)  $(INCLUDES) $(DEFS)  #../../Test/Src/alg_malloc.c 
#buffermanager.obj:
#	$(CC)     $(CFLAGS_XDC) $(CFLAGS) $(OUTFILE)  $(INCLUDES) $(DEFS)  #../../Test/Src/buffermanager.c 
#crc.obj:
#	$(CC)     $(CFLAGS_XDC) $(CFLAGS) $(OUTFILE)  $(INCLUDES) $(DEFS)  ../../Test/Src/crc.c 
#mpeg2venc.obj:
#	$(CC)     $(CFLAGS_XDC) $(CFLAGS) $(OUTFILE)  $(INCLUDES) $(DEFS)  #../../Test/Src/mpeg2venc.c 
LockMP.obj:
	$(CC)     $(CFLAGS_XDC) $(CFLAGS) $(OUTFILE)  $(INCLUDES) $(DEFS)  ../../Test/Src/LockMP.c	
hdvicp_framework.obj:
	$(CC)     $(CFLAGS_XDC) $(CFLAGS_1) $(OUTFILE)  $(INCLUDES) $(DEFS)  ../../Test/Src/hdvicp_framework.c
mpeg2venc_ti_formatconvt.obj:	
	$(CC)     $(CFLAGS_XDC) $(CFLAGS_1) $(OUTFILE)  $(INCLUDES) $(DEFS) ../../Test/Src/mpeg2venc_ti_formatconvt.c
myLinuxutils.obj:
	$(CC)     $(CFLAGS_XDC) $(CFLAGS) $(OUTFILE)  $(INCLUDES) $(DEFS)  ../../Test/Src/myLinuxutils.c
mpeg2venc_ti_api.obj:
	$(CC)     $(CFLAGS_XDC) $(CFLAGS) $(OUTFILE)  $(INCLUDES) $(DEFS)  ../../Test/Src/mpeg2venc_ti_api.c
testapp_idma.obj:
	$(CC)     $(CFLAGS_XDC) $(CFLAGS) $(OUTFILE)  $(INCLUDES) $(DEFS)  ../../Test/Src/testapp_idma.c 
testapp_arm926intc.obj:
	$(CC)     $(CFLAGS_1) $(OUTFILE)  $(INCLUDES) $(DEFS)  ../../Test/Src/testapp_arm926intc.c 
testapp_inthandler.obj:
	$(CC)     $(CFLAGS_1) $(OUTFILE)  $(INCLUDES) $(DEFS)     ../../Test/Src/testapp_inthandler.asm 
testapp_intvecs.obj:
	$(CC)     $(CFLAGS_1) $(OUTFILE)  $(INCLUDES) $(DEFS)     ../../Test/Src/testapp_intvecs.asm 
testapp_mmutable.obj:
	$(CC)     $(CFLAGS_1) $(OUTFILE)  $(INCLUDES) $(DEFS)     ../../Test/Src/testapp_mmutable.asm 
#mpeg2venc_ti_configparser.obj:
#	$(CC)     $(CFLAGS_XDC) $(CFLAGS) $(OUTFILE)  $(INCLUDES) $(DEFS)  #../../Test/Src/mpeg2venc_ti_configparser.c 
mpeg2venc_ti_arm926testapp.obj:
	$(CC)     $(CFLAGS_XDC) $(CFLAGS_1) $(OUTFILE)  $(INCLUDES) $(DEFS)  ../../Test/Src/mpeg2venc_ti_arm926testapp.c
#ires_algorithm.obj:
#	$(CC)     $(CFLAGS_XDC) $(CFLAGS) $(OUTFILE)  $(INCLUDES) $(DEFS)  ../../Test/Src/ires_algorithm.c 
#dummyTest.obj:
#	$(CC)     $(CFLAGS_XDC) $(CFLAGS) $(OUTFILE)  $(INCLUDES) $(DEFS)  ../../Test/Src/dummyTest.c 

$(CONFIG)/linker.cmd $(CONFIG)/compiler.opt : $(CONFIG).cfg
	xs xdc.tools.configuro -c $(CGTOOLS) -t $(XDCTARGET) -p $(XDCPLATFORM) $<

clean:
	del *.obj
