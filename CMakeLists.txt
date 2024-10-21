cmake_minimum_required(VERSION 3.26)
project(OOP)

set(CMAKE_CXX_STANDARD 17)

add_executable(OOP main.cpp seagame/ship.h seagame/src/ship.cpp
        seagame/src/game_field.cpp
        seagame/game_field.h
        seagame/ship_manager.h
        seagame/src/ship_manager.cpp
        seagame/point.h
        seagame/field_cell.h)
    