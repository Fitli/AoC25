cmake_minimum_required(VERSION 3.16)
project(aoc2025)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -Ofast)

add_executable(aoc2025 main.cpp
        infra/Task.h
        tasks/Day01.h
        tasks/Day03.h
        tasks/Day04.h
        tasks/Day05.h
        helper/string_manipulation.h
        tasks/Day06.h
)
