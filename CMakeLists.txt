
cmake_minimum_required(VERSION 3.1)

project(TXTencrypter LANGUAGES CXX)

add_compile_options(-g)
add_compile_options(-Wall -Wextra)
add_compile_options(-Werror)
add_compile_options(-std=c++11)

set(SRC
    src/main.cpp 
    src/application.cpp 
    src/mangler.cpp 
    src/encryptengine.cpp 
    src/hash.cpp
    src/filehandler.cpp
    src/configuration.cpp
)

set(INC
    inc/application.hpp 
    inc/ascii_avoid_list.hpp
    inc/encryptengine.hpp 
    inc/filehandler.hpp
    inc/mangler.hpp 
    inc/configuration.hpp
)

include_directories(inc)

add_executable(TXTencrypter ${INC} ${SRC})