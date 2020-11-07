@echo off
set VSCMD_START_DIR=.
call "J:\Visual Studio 2017\VC\Auxiliary\Build\vcvars32.bat"
lib /machine:"x86" %*
