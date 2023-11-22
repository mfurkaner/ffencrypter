@echo off&&cls
cd ../src
g++ -g main.cpp hash.cpp encryptengine.cpp mangler.cpp application.cpp configuration.cpp filehandler.cpp -o ../zEncrypter.exe -std=c++11
cd ..
zEncrypter.exe