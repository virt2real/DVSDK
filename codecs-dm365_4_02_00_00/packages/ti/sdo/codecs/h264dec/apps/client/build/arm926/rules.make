#Set the compiler option to be used for building testapp. Changes path of the tools as per compiler option. 
#mvl = Montvista Cross Compiler, cst = CodeSourcery_Toolchain
COMPILER = mvl

# Set location of various tools
XDC_INSTALL_DIR=/db/swcoe_asp/DM360_Codecs/xdctools_3_15_01_59
LINUXKERNEL_INSTALL_DIR=/opt/montavista/pro/devkit/lsp/ti-davinci
MVTOOL_DIR=/opt/montavista/pro/devkit/arm/v5t_le
MVTOOL_PREFIX=$(MVTOOL_DIR)/bin/arm_v5t_le-
CGTOOLS=$(MVTOOL_DIR)
FC_INSTALL_DIR = /db/swcoe_asp/DM360_Codecs/framework_components_2_25_02_06
LINUXUTILS_INSTALL_DIR = /db/swcoe_asp/DM360_Codecs/linuxutils_2_25_04_10
XDAIS_INSTALL_DIR = /db/swcoe_asp/DM360_Codecs/xdais_6_25_02_11
CE_INSTALL_DIR = /db/swcoe_asp/DM360_Codecs/codec_engine_2_24
