cmake_minimum_required(VERSION 3.26)
project(DES_decryption)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fopenmp")

add_executable(DES_decryption main.cpp
        common.h
        common.cpp
        utility.cpp
        utility.h
        testing.cpp
        testing.h)
