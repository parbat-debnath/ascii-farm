@echo off

gcc src/*.c -o ASCIIFarm.exe -lwinmm

start /max cmd /c ASCIIFarm.exe