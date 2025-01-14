cmake_minimum_required(VERSION 3.17)
project(serwer C)

set(CMAKE_C_STANDARD 11)

add_executable(serwer main.c cmake-build-debug/function.c function.h)