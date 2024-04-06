@echo off
del a.exe
g++ %1.cpp -std=c++17 -O3 -fwhole-program -fconcepts -DLOCAL
clean %1
a