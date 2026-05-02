cmake_minimum_required(VERSION 4.2)
project(AC_Waveform_Analyser C)

set(CMAKE_C_STANDARD 11)

add_executable(AC_Waveform_Analyser main.c
        waveform.c
        waveform.h
        io.c
        io.h)
