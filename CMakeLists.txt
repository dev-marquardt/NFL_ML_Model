cmake_minimum_required(VERSION 4.4)
project(CFD_ML C)

set(CMAKE_C_STANDARD 11)

add_executable(CFD_ML main.c
        ModelNFL.h
        ModelNFL.c
        ModelNFL.c
        ModelNFL.c
        ModelNFL.c
        RawDataInput.h
        RawDataInput.c
        mathFunctions.h
        mathFunctions.c)
