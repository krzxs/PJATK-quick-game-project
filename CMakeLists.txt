cmake_minimum_required(VERSION 3.30)
project(PJC)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 11.0.2
)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML
        GIT_TAG 2.6.2
)

FetchContent_MakeAvailable(fmt SFML)

add_executable(PJC main.cpp
        entity/entity.cpp
        entity/entity.hpp
        entity/entity_living.cpp
        entity/entity_living.hpp
        entity/player.cpp
        entity/player.hpp
        gfx/animation.cpp
        gfx/animation.hpp
        gfx/animation_controller.cpp
        gfx/animation_controller.hpp
        game/game.cpp
        game/game.hpp
        entity/movement_controller.cpp
        entity/movement_controller.hpp
        entity/direction.cpp
        entity/direction.hpp
        entity/hitbox_controller.cpp
        entity/hitbox_controller.hpp
        entity/coin.cpp
        entity/coin.hpp
        entity/collidable.hpp
        gfx/tile.cpp
        gfx/tile.hpp
        gfx/tilemap.cpp
        gfx/tilemap.hpp
        entity/ball.cpp
        entity/ball.hpp
        gfx/coin_counter.cpp
        gfx/coin_counter.hpp
        gfx/gui_counter.cpp
        gfx/gui_counter.hpp
        gfx/hp_counter.cpp
        gfx/hp_counter.hpp
        entity/enemy.cpp
        entity/enemy.hpp
        entity/follow_component.cpp
        entity/follow_component.hpp
        entity/enemy_ball.cpp
        entity/enemy_ball.hpp
        game/state_base.hpp
        game/main_menu_state.cpp
        game/main_menu_state.hpp
        game/gameplay_state.cpp
        game/gameplay_state.hpp
        gfx/button.cpp
        gfx/button.hpp
        game/game_utils.cpp
        game/game_utils.hpp
)
target_link_libraries(PJC fmt sfml-graphics)
