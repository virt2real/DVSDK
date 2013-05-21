echo off

REM ======== sim6416 ========
REM @set executable="C:\CCStudio_v3.1\bios_5_20_05\packages\ti\bios\examples\basic\swi\sim6416\Debug\swi.out"
REM @set executable="C:\CCStudio_v3.1\bios_5_20_05\packages\ti\bios\examples\advanced\semaphore\sim6416\Debug\semaphore.out"
REM @set executable="C:\CCStudio_v3.1\bios_5_20_05\packages\ti\bios\examples\basic\mem_management\sim6416\Debug\mem_management.out"
REM @set executable="C:\CCStudio_v3.1\bios_5_20_05\packages\ti\bios\examples\basic\mailbox\sim6416\Debug\mailbox.out"
REM @set executable="C:\CCStudio_v3.1\bios_5_20_05\packages\ti\bios\examples\basic\bigtime\sim6416\Debug\bigtime.out"

REM ======== eZdsp2812 ========
REM @set executable="C:\CCStudio_v3.1\bios_5_20_05\packages\ti\bios\examples\basic\tsk\ezdsp2812\Debug\tsk.out"

REM ======== Configs ========
REM @set config="C:/Program Files/Texas Instruments/CCSv4.0.0.7.36/CCSv4/common/targetdb/configurations/tisim_da830_pv.ccxml"

REM @set config="C:\Program Files\Texas Instruments\CCSv4.0.0.7.36\CCSv4\common\targetdb\configurations\tisim_c64xxle_ca.ccxml"
REM @set isa=100

REM @set config="C:\Program Files\Texas Instruments\CCSv4.0.0.7.36\CCSv4\common\targetdb\configurations\f2812_ppemulator_0x378.ccxml"
REM @set isa=40

REM @set config="C:\Program Files\Texas Instruments\CCSv4.0.0.7.36\CCSv4\common\targetdb\configurations\tisim_c55x30_ca.ccxml"
REM @set isa=85

echo on

@set DebugServer="C:\Program Files\Texas Instruments\CCSv4.0.0.7.36\CCSv4\DebugServer\win32"
@set config="C:\Program Files\Texas Instruments\CCSv4.0.0.7.36\CCSv4\common\targetdb\configurations\tisim_c64xxle_ca.ccxml"
@set executable="C:\CCStudio_v3.1\bios_5_20_05\packages\ti\bios\examples\advanced\semaphore\sim6416\Debug\semaphore.out"
@set command="m xdc.rov.bios5.LOG Logs"
@set isa=100

xs -Dxdc.rov.traceEnable=true -DXPCOM.RUNTIME=%DebugServer% xdc.rov.dss %config% %executable% %command% %isa%
