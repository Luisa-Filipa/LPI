cmake_minimum_required(VERSION 3.12.1)
project(projetoparte2 C)

set(CMAKE_C_STANDARD 99)

add_executable(projetoparte2 main.c mergesort/mergesort.c mergesort/mergesort.h projeto.c projeto.h)