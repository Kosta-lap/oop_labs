cmake_minimum_required(VERSION 3.26)
project(OOP)

set(CMAKE_CXX_STANDARD 17)

add_executable(OOP main.cpp seagame/src/game/core/ship.h seagame/src/game/core/ship.cpp
        seagame/src/game/core/game_field.cpp
        seagame/src/game/core/game_field.h
        seagame/src/game/core/ship_manager.h
        seagame/src/game/core/ship_manager.cpp
        seagame/src/game/utils/point.h
        seagame/src/game/utils/field_cell.h
        seagame/src/abilities/interfaces/ability_interface.h
        seagame/src/abilities/effects/double_damage.cpp
        seagame/src/abilities/effects/double_damage.h
        seagame/src/abilities/effects/scanner.cpp
        seagame/src/abilities/effects/scanner.h
        seagame/src/abilities/effects/random_shot.cpp
        seagame/src/abilities/effects/random_shot.h
        seagame/src/abilities/core/ability_manager.cpp
        seagame/src/abilities/core/ability_manager.h
        seagame/src/abilities/interfaces/ability_factory.h
        seagame/src/abilities/factories/double_damage_factory.cpp
        seagame/src/abilities/factories/double_damage_factory.h
        seagame/src/abilities/factories/scanner_factory.cpp
        seagame/src/abilities/factories/scanner_factory.h
        seagame/src/abilities/factories/random_shot_factory.cpp
        seagame/src/abilities/factories/random_shot_factory.h
        seagame/src/abilities/core/ability_production.cpp
        seagame/src/abilities/core/ability_production.h
        seagame/src/game/errors/place_error.h
        seagame/src/game/errors/out_of_bounds_error.h
        seagame/src/abilities/errors/ability_extract_error.h
        seagame/src/common/command.h
        seagame/src/abilities/core/add_new_ability.h
        seagame/src/abilities/core/add_new_ability.cpp
        seagame/src/game/core/game_state.cpp
        seagame/src/game/core/game_state.h
        seagame/src/game/core/game.cpp
        seagame/src/game/core/game.h
        seagame/src/common/FileWrapper.cpp
        seagame/src/common/FileWrapper.h
        seagame/src/game/core/game_save_loader.cpp
        seagame/src/game/core/game_save_loader.h
)
    