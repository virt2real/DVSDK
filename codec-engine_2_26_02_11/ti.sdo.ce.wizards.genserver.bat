@rem See http://processors.wiki.ti.com/index.php/Codec_Engine_GenServer_Wizard_FAQ
@rem for further documentation

@rem User: set this variable to point your XDC installation.
@if "%XDC_INSTALL_DIR%"=="" set XDC_INSTALL_DIR=c:\xdc_3_16_00_18

@for %%f in (%0) do @set thisDir=%%~dpf

"%XDC_INSTALL_DIR%\xs" --xdcpath="%thisDir%packages" ti.sdo.ce.wizards.genserver %1 %2 %3 %4 %5 %6 %7 %8 %9
