@echo off
setlocal
IF NOT DEFINED MSYS2_PATH_TYPE set MSYS2_PATH_TYPE=minimal
set CHERE_INVOKING=1
C:\msys64\usr\bin\bash.exe -leo pipefail %*