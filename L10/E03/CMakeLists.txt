cmake_minimum_required(VERSION 3.12)
project(Prova)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Prova
        grafo.txt
        graph.c
        graph.h
        main.c
        ST.c
        ST.h)
