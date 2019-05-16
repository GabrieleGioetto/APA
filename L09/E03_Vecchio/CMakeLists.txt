cmake_minimum_required(VERSION 3.12)
project(E03 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(E03
        inventario.c
        inventario.h
        main.c
        personaggi.c
        personaggi.h)
