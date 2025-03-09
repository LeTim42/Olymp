@echo off
del a.exe 2> null
del null
g++ %1 -std=c++17 -O2 -fwhole-program -fconcepts -DLOCAL -I olymp
include < %1 | clean | clip
a