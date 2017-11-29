cmake_minimum_required(VERSION 3.8)
project(openmp_problem_1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(openmp_problem_1 ${SOURCE_FILES})

find_package(OpenMP)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} $OpenMP_CXX_FLAGS}")