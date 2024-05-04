cmake_minimum_required(VERSION 3.22)
project(filter_more C)

set(CMAKE_C_STANDARD 99)

add_executable(filter_more filter.c bmp.h helpers.h helpers.c)
