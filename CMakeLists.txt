cmake_minimum_required(VERSION 3.26)
project(OOP)

set(CMAKE_CXX_STANDARD 17)

add_executable(OOP main.cpp seagame/ship.h seagame/src/ship.cpp
        seagame/src/game_field.cpp
        seagame/game_field.h
        seagame/ship_manager.h
        seagame/src/ship_manager.cpp
        seagame/point.h
        seagame/field_cell.h
        seagame/ability_interface.h
        seagame/src/double_damage.cpp
        seagame/double_damage.h
        seagame/src/scanner.cpp
        seagame/scanner.h
        seagame/src/random_shot.cpp
        seagame/random_shot.h
        seagame/src/ability_manager.cpp
        seagame/ability_manager.h
        seagame/ability_name.h
        seagame/ability_builder.h
        seagame/src/double_damage_builder.cpp
        seagame/double_damage_builder.h
        seagame/src/scanner_builder.cpp
        seagame/scanner_builder.h
        seagame/src/random_shot_builder.cpp
        seagame/random_shot_builder.h
        seagame/src/ability_production.cpp
        seagame/ability_production.h)
    