cmake_minimum_required(VERSION 3.15)
project(vector)

set(CMAKE_CXX_STANDARD 14)
add_executable(vector vector.hpp exceptions.hpp utility.hpp class-bint.hpp class-integer.hpp class-matrix.hpp code3.cpp)

