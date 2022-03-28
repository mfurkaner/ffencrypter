@echo off&&cls
cd ../src
g++ -g -g tests.cpp hash.cpp encryptengine.cpp mangler.cpp application.cpp ../test/test_hash.cpp -o ../test.exe -std=c++11
cd ..
test.exe