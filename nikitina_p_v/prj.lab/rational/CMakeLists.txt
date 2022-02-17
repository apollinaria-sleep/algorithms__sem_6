cmake_minimum_required(VERSION 3.21)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
project(untitled5)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled5 rational.h rational.cpp tests.cpp doctest.h)