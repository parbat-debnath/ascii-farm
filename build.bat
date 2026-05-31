@echo off
gcc src/*.c -O2 -static -static-libgcc -o ASCIIFarm.exe -lwinmm
start /max "" cmd /c ASCIIFarm.exe