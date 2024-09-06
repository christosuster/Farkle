cmake_minimum_required(VERSION 3.29)
project(Farkle)

set(CMAKE_CXX_STANDARD 26)

add_executable(Farkle
        application.h
gameRules.txt
        application.cpp
        die.cpp
        die.h
        player.cpp
        player.h)
