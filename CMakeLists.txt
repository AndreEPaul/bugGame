cmake_minimum_required(VERSION 3.15)
project(finalProject)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(finalProject
        Die.cpp
        Die.hpp
        Lettuce.hpp
        main.cpp
        Menu.cpp
        Menu.hpp
        Puddle.hpp
        Rock.hpp
        Space.hpp)
