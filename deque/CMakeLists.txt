cmake_minimum_required(VERSION 3.15)
project(deque)

set(CMAKE_CXX_STANDARD 14)

add_executable(deque exceptions.hpp utility.hpp class-matrix.hpp class-integer.hpp class-bint.hpp code2.cpp dequepp.hpp)