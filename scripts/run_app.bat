@echo off&&cls
cd ../src
g++ -g main.cpp hash.cpp encryptengine.cpp application.cpp -o ../txtencrypter.exe -std=c++11
cd ..
txtencrypter.exe