cmake_minimum_required(VERSION 3.12)
project(p C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(p
        equipArray.c
        equipArray.h
        inv.c
        inv.h
        invArray.c
        invArray.h
        main.c
        pg.c
        pg.h
        pgList.c
        pgList.h stat.c stat.h)
