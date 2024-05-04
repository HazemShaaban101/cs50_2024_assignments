cmake_minimum_required(VERSION 3.22)
project(filter_less C)

set(CMAKE_C_STANDARD 99)

add_executable(filter_less filter.c bmp.h helpers.c helpers.h)
