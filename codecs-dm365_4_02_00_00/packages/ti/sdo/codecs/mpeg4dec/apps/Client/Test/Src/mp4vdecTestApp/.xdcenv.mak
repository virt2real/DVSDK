#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /db/swcoe_asp/DM360_Codecs/framework_components_2_23_00_03/fctools/packages;/db/swcoe_asp/DM360_Codecs/framework_components_2_23_00_03/packages;/db/swcoe_asp/DM360_Codecs/framework_components_2_23_00_03/examples;/db/swcoe_asp/DM360_Codecs/xdctools_3_15_00_10/packages
override XDCROOT = /db/swcoe_asp/DM360_Codecs/xdctools_3_15_00_10
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /db/swcoe_asp/DM360_Codecs/framework_components_2_23_00_03/fctools/packages;/db/swcoe_asp/DM360_Codecs/framework_components_2_23_00_03/packages;/db/swcoe_asp/DM360_Codecs/framework_components_2_23_00_03/examples;/db/swcoe_asp/DM360_Codecs/xdctools_3_15_00_10/packages;/db/swcoe_asp/DM360_Codecs/xdctools_3_15_00_10/packages;..
HOSTOS = Linux
endif
