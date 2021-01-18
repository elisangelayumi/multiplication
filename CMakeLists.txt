cmake_minimum_required(VERSION 3.15)
project(multiplication)

set(CMAKE_CXX_STANDARD 14)

add_executable(multiplication multiplication.cpp grandentier.cpp tests.cpp)