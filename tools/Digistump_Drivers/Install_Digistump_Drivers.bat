@echo off
echo Detecting OS processor type
echo Launching Driver Installer

@echo off
if "%PROCESSOR_ARCHITECTURE%" == "AMD64" (
  DPinst64.exe
) ELSE IF "%PROCESSOR_ARCHITEW6432%" == "AMD64" (
  DPinst64.exe
) ELSE (
  DPinst.exe %ARGS%
)
