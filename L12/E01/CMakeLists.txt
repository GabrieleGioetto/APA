cmake_minimum_required(VERSION 3.12)
project(E01 C)

set(CMAKE_C_STANDARD 99)

add_executable(E01 main.c graph.c graph.h ST.c ST.h)