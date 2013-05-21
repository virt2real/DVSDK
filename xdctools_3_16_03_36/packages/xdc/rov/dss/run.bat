@echo off

@set CCSv4=C:/Program Files/Texas Instruments/CCSv4

@set Path=%Path%;%CCSv4%/DebugServer/bin/win32;%CCSv4%/DebugServer/win32;%CCSv4%/common/uscif;%CCSv4%/common/bin
@set XDCPATH=%XDCPATH%;%CCSv4%/DebugServer/packages;

@set DebugServer="%CCSv4%/DebugServer/win32"

REM ======== Configs ========
REM @set config="C:/Program Files/Texas Instruments/CCSv4.0.0.7.36/CCSv4/common/targetdb/configurations/tisim_da830_pv.ccxml"

REM @set config="C:\Program Files\Texas Instruments\CCSv4.0.0.7.36\CCSv4\common\targetdb\configurations\tisim_c64xxle_ca.ccxml"
REM @set isa=100

REM @set config="C:\Program Files\Texas Instruments\CCSv4.0.0.7.36\CCSv4\common\targetdb\configurations\f2812_ppemulator_0x378.ccxml"
REM @set isa=40

REM @set config="C:\Program Files\Texas Instruments\CCSv4.0.0.7.36\CCSv4\common\targetdb\configurations\tisim_c55x30_ca.ccxml"
REM @set isa=85

@set config="C:\Documents and Settings\a0271099\My Documents\workspace\Stairstep\PrimusSim.ccxml"
@set isa=100

@set executable="V:/cmcc/avala-k09x/src/ti/sysbios/rta/apps/debug/MultiLogTest.x674"
@set command="m ti.sysbios.knl.Task Basic"

xs -Dxdc.rov.traceEnable=true -DXPCOM.RUNTIME=%DebugServer% xdc.rov.dss %config% %executable% %command% %isa%
