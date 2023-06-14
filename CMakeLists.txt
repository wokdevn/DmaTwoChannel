cmake_minimum_required(VERSION 3.15)
project(TwoDma C)

set(CMAKE_C_STANDARD 99)

add_executable(TwoDma src/main.c head/interdma.h src/utilMM2S.c head/utilMM2S.h)