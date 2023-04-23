cmake_minimum_required(VERSION 3.16)
project(CSM)

set(CMAKE_CXX_STANDARD 17)

add_executable(CSM main.cpp tools.h alg.cpp alg.h)
