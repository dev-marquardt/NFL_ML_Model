cmake_minimum_required(VERSION 4.4)
project(CFD_ML C)

set(CMAKE_C_STANDARD 11)

add_executable(CFD_ML main.c
        ModelCFD.h
        ModelCFD.c
        ModelCFD.c
        ModelCFD.c
        ModelCFD.c
        RawDataInput.h
        RawDataInput.c)
