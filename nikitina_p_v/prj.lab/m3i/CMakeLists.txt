cmake_minimum_required(VERSION 3.21)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
project(m3i)

set(CMAKE_CXX_STANDARD 17)

add_library(m3i m3i.h m3i.cpp m3i_test.cpp)
add_executable(m3i_test m3i_test.cpp)
target_link_libraries(m3i_test m3i)
