cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 17)

add_library(rational rational.h rational.cpp)
add_executable(rational_test test_rational.cpp)
target_link_libraries(rational_test rational)
