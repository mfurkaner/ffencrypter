
cmake_minimum_required(VERSION 3.1)

project(TXTencrypter LANGUAGES CXX)

add_compile_options(-g)

add_compile_options(-Wall -Wextra)

add_compile_options(-std=c++11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_executable(TXTencrypter src/main.cpp src/application.cpp src/mangler.cpp src/encryptengine.cpp src/hash.cpp src/filehandler.cpp)