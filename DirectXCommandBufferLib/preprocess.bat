@echo off
REM This script assumes that cl.exe is in your path

echo Deleting PREPROCESSED_%1
REM del /F PREPROCESSED_%1

echo Calling compiler to preprocess %1 into PREPROCESSED_%1
cl -EP -C -D CBD3D_PREPROCESSING %1 > PREPROCESSED_%1

echo Beautifying PREPROCESSED_%1
REM configuration of GC is found in GC.cfg
GC -file-PREPROCESSED_%1

echo Make read only
REM attrib +R PREPROCESSED_%1
