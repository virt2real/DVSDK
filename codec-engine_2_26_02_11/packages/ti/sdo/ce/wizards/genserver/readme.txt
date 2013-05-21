******************************************************************************
Codec Engine GenServer Wizard
******************************************************************************

------------------------------------------------------------------------------
Introduction
------------------------------------------------------------------------------
The Codec Engine GenServer Wizard generates the XDC files necessary to create
a server package for the Codec Engine.

------------------------------------------------------------------------------
Pre-requisites
------------------------------------------------------------------------------
Please see Codec Engine release notes for the version dependencies 
needed to run the wizard and build the server.
 
Your XDCPATH should contain:
  $(CE_INSTALL_DIR)/packages
  $(CE_INSTALL_DIR)/cetools/packages OR the repositories for XDAIS, FC, CMEM, 
      and BIOSUTILS
  $(DSPLINK_INSTALL_DIR)
  <your repository containing codec packages>

------------------------------------------------------------------------------
Usage
------------------------------------------------------------------------------

To start the graphical version, use: xs ti.sdo.ce.wizards.genserver

This will allow you to enter all of the information needed to create a package.

If you prefer to use the command line option, follow the directions below.

To run the command line wizard:
xs ti.sdo.ce.wizards.genserver -f=xmlFileName

The XML file must have been previously saved with the graphical
version of the wizard.

The graphical version has its own "Help" available in the GUI menu

------------------------------------------------------------------------------
Release Instructions
------------------------------------------------------------------------------
After generating files using the Codec Engine GenServer Wizard, edit codec.cfg.
Assign values to any settings that are undefined:

Example: Original line: VIDDEC_COPY.alg.codeSection = undefined;
Modified line: VIDDEC_COPY.alg.codeSection = "DDR2";
Don't forget the quotes!

Run "gmake all" to generate the server executable from the destination 
directory (destination directory + server.package.name.with.dots.turned.into.
forward.slashes).

------------------------------------------------------------------------------
Known Issues
------------------------------------------------------------------------------
ID    Headline
----  --------
1576  Add xdoc from CE/FC to wizard templates 

The Package Search Path dialog raises an error on Linux with XDC Tools v3.10.
 To work around, modify the XDCPATH environment variable to contain the desired
search directories prior to starting the Wizard.

Changes since 0.2.3:
	Support for multiple codecs
	GUI rework
        Scratch group config

------------------------------------------------------------------------------
FAQ
------------------------------------------------------------------------------
The FAQ is available on the TI ExpressDSP Wiki page:
http://tiexpressdsp.com/index.php?title=Codec_Engine_GenServer_Wizard_FAQ
