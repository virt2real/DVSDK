@echo off
REM =========================================================================
REM ||  This file is a wrapper around the Rhino javascript engine.  It sets-up 
REM ||  the necessary classpaths and command-line arguments and then invokes
REM ||  the Java runtime.

setlocal

REM *************************************************************************
REM  This path to points to the absolute install location of the Debug Server
REM *************************************************************************
if defined DEBUGSERVER (
    set foo=
) else (
    set DEBUGSERVER=C:\Program Files\Texas Instruments\CC Essentials v3.1\DebugServer
)

REM Path to Rhino JAR File
set RHINO_JAR="%DEBUGSERVER%\scripting\lib\rhino\js.jar"

REM Path to DebugServer JAR File
set SCRIPTING_JARS="%DEBUGSERVER%\scripting\lib\dss.jar"

if not exist %RHINO_JAR% (
  "%DEBUGSERVER%\..\scripting\bin\dss.bat" %~dp0/load_ccs.xs  -c %~dp0/TargetConfiguration.ccxml -a %*
  if errorlevel 1 exit 1
  exit 0
)
  
REM *************************************************************************
set PATH=%DEBUGSERVER%\scripting\lib;%PATH%
set PATH=%DEBUGSERVER%\bin\win32;%PATH%
set PATH=%DEBUGSERVER%\win32\components;%PATH%
set PATH=%DEBUGSERVER%\win32\drivers;%PATH%
REM *************************************************************************

REM Name of Rhino Shell Java Application
set RHINO_SHELL=org.mozilla.javascript.tools.shell.Main

REM Name of Rhino Debugger Java Application
set RHINO_DEBUGGER=org.mozilla.javascript.tools.debugger.Main

REM If the user chose to install the JRE with this DSS install - use that
REM JRE.  Otherwise use whatever is on the PATH

REM In stand-alone DSS - the installed jre is in INSTALLDIR\jre.  Check 
REM here first
if exist %DEBUGSERVER%\..\jre (
  set JAVA_HOME=%DEBUGSERVER%\..\jre
  set PATH=%DEBUGSERVER%\..\jre\bin;%PATH%
)

REM In CCE/CCS - the installed jre is in INSTALLDIR\eclipse\jre.  Check 
REM here next
if exist %DEBUGSERVER%\..\eclipse\jre (
  set JAVA_HOME=%DEBUGSERVER%\..\eclipse\jre
  set PATH=%DEBUGSERVER%\..\eclipse\jre\bin;%PATH%
)

REM =========================================================================
REM Launch Rhino script engine.  Import the scripting package.
"%JAVA_HOME%\bin\java.exe" -DXPCOM.RUNTIME="%DEBUGSERVER%\win32" -cp %RHINO_JAR%;%SCRIPTING_JARS% %RHINO_SHELL% %~dp0/load.xs  -c %~dp0/SystemSetup.xml -a %*
endlocal


