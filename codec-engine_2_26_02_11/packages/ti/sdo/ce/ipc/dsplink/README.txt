
How to add support for a new DSP/BIOS Link port
============================================================================

Overview

    When using DSP/BIOS Link as the transport between the GPP and the DSP,
    there is a small amount of code in Codec Engine which has compile-time
    bindings to the device model. In addition, there is a small amount of
    DSP/BIOS Link configuration which also has bindings to the device model.
    The code and configuration parameters are managed by this package:
    ti.sdo.ce.ipc.dsplink. This package is pre-compiled against the release
    of DSP/BIOS Link which ships in the <product>/cetools/packages repository.

    If you have your own release of DSP/BIOS Link which you are porting to
    a new device, then you will need to modify this package and compile it
    against your own DSP/BIOS Link release. When building the Codec Engine
    examples, or your own applications, you must place your copy of this
    package on the XDC package path in front of the Codec Engine release
    to ensure you package is used instead of the one shipped in the Codec
    Engine release.

    This file describes the steps to accomplish this.


1.  Setup a work area. For this example, I will assume you have created
    your work area as follows. Note: it is not necessary to have all the
    installations in the same folder; adjust your paths accordingly.

    XDC             -> /usr/work/xdc_3_00_06
    CE              -> /usr/work/codec_engine_2_20
    examples        -> /usr/work/examples
    user.bld        -> /usr/work/examples/user.bld
    xdcpaths.mak    -> /usr/work/examples/xdcpaths.mak
    local           -> /usr/work/local
    dsplink         -> /usr/work/port/dsplink

    Where examples is your copy of the codec_engine_2_20/examples folder.
    
    Where user.bld is the build script you have modified with the install
    paths for your codegen tools.

    Where xdcpaths.mak is the makefile you have modified with your
    installation paths.

    Where local is a folder (repository) we will use for installing and
    building the ti.sdo.ce.ipc.dsplink package.

    Where dsplink is your own DSP/BIOS Link release. Note the use of 
    /usr/work/port as the repository for your Link release. I recommend
    placing your Link in its own repository to isolate it from other
    packages.


2.  Unpack the ti.sdo.ce.ipc.dsplink archive file into your local repository
    you created above.

    cd /usr/work/local
    tar xf ../codec_engine_2_20/packages/ti/sdo/ce/ipc/dsplink/ti_sdo_ce_ipc_dsplink.tar


3.  Set the macros in the package makefile to point to your installation.
    We will start by using the DSP/BIOS Link that ships with Codec Engine
    and once the build is working, then change to use your DSP/BIOS Link.

    cd /usr/work/local/ti/sdo/ce/ipc/dsplink
    edit makefile

    XDC_INSTALL_DIR := /usr/work/xdc_3_10
    CE_INSTALL_DIR  := /usr/work/codec_engine_2_20
    DSPLINK_REPO    := $(CE_INSTALL_DIR)/cetools/packages
    USER_BLD        := /usr/examples


4. Edit the buildDspLink.xs to comment out the line:

        "ti/sdo/ce/ipc/dsplink/Power_dsplink.c",

    in the variable objs[], if your device does not support power control.

    cd /usr/work/local/ti/sdo/ce/ipc/dsplink
    edit buildDspLink.xs

5.  Test the build script. After you clean the package, the lib folder may or
    may not be empty, depending on what targets are enabled in your user.bld
    script. If it's not empty, you can remove all the files in lib, and
    subsequent clean builds will empty the lib folder.
    After you build the package, the lib folder should have some
    libraries in it.

    cd /usr/work/local/ti/sdo/ce/ipc/dsplink
    make .interfaces
    make clean
    make


6.  Now we will integrate your own DSP/BIOS Link release. Start by editing
    the makefile again and pointing the DSPLINK_REPO macro to your own
    Link release.

    cd /usr/work/local/ti/sdo/ce/ipc/dsplink
    edit makefile

    DSPLINK_REPO    := /usr/work/port


7.  Create the dsplink configuration file. Copy one of the existing
    Processor_dsplink_linkcfg_<device>.c files in this package or copy the
    generated configuration file from your own release located at
    
    /usr/work/port/dsplink/config/all/CFG_<device>.c

    In this example, I'll use OMAP2530 as my new device and create the
    following new file:

    Processor_dsplink_linkcfg_OMAP2530.c

    Edit your new file and modify it as needed. Important: if you copied
    the configuration file from your own Link release, then you will need
    to add the following at the top of your file:

    #define LINKCFG_config ti_sdo_ce_ipc_Processor_linkcfg
    #define LINKCFG_gppOsObject ti_sdo_ce_ipc_Processor_linkcfg_OS
    #undef  CONST
    #define CONST


8.  Add new device file to your package.bld script. Copy and paste one
    of the if-statements inside the loop and modify the library name and
    source filename as needed. In this example, I would use the OMAP3530
    block and make the following changes.

    cd /usr/work/local/ti/sdo/ce/ipc/dsplink
    edit package.bld

    lib name -> "lib/ipc_dsplink_2530"
    filename -> "Processor_dsplink_linkcfg_OMAP2530.c"

    Set your new if-statement to true and all others to false. Only your
    new library will be built and none of the others (which would fail
    because your release of Link probably does not support them).


9.  Edit the DspLinkCfg.xdc specification file to add your device's specific
    DSP/BIOS Link configuration parameters.
    
    cd /usr/work/local/ti/sdo/ce/ipc/dsplink
    edit DspLinkCfg.xdc
    
    Currently, this consists of the default memory map and the power control
    parameter. Once again, copy and paste an existing block and then modify
    it as needed. NB: the array index (which is a string) must match the
    device name as specified by RTSC. You must have an XDC specification
    file for your device in your XDC installation. For this example, the
    file would be

    /usr/work/xdc_3_00_06/packages/ti/catalog/c6000/TMS320C2530.xdc


10.  Edit the package.xs script to add your new library to the build model.

    cd /usr/work/local/ti/sdo/ce/ipc/dsplink
    edit package.xs
    
    Once again, copy and paste an existing block and modify the library
    name to match the same name used in the package.bld script. Do not add
    the library suffix; the script adds it for you using the target's suffix.
    Also update the regular expression used to match your device name. For
    this example, I would add the following.

    else if (prog.cpu.deviceName.match(/C2530$/)) {
        lib = "lib/ipc_dsplink_2530";
    }


11. Clean and rebuild your package. Verify that your library is in the lib
    folder.

    cd /usr/work/local/ti/sdo/ce/ipc/dsplink
    make .interfaces
    make clean
    make


12. Finally, you need to add your new package and our own DSP/BIOS Link
    package to the XDC path in front of the Codec Engine installation in
    order to replace the ones delivered in the product. Edit the xdcpaths.mak
    file located in your examples folder.
    
    cd /usr/work/examples
    edit xdcpaths.mak

    At the bottom of this file, add your local repository which contains your
    copy of this package and your Link repository to the XDC path. Be sure to
    add them at the front.

    XDC_PATH := /usr/work/local;/usr/work/port;$(XDC_PATH)

    You should now be able to rebuild a Codec Engine example and link with
    your own port of DSP/BIOS Link for your new device.
