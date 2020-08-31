cmake_minimum_required(VERSION 3.15)
project(map)

set(CMAKE_CXX_STANDARD 14)

add_executable(map map1.hpp class-bint.hpp class-integer.hpp class-matrix.hpp exceptions.hpp utility.hpp code2.cpp)