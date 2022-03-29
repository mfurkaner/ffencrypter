@echo off&&cls
cd ../build/debug
cmake ../..
make
clear
TXTencrypter.exe