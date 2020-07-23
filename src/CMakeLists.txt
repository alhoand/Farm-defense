add_subdirectory(enemies)
add_subdirectory(towers)

target_sources(TowerDefense
    PRIVATE
        bullet.hpp
        bullet.cpp
        enemy.hpp
        enemy.cpp
        game.hpp
        game.cpp
        game_field.hpp
        game_field.cpp
        main.cpp
        position.hpp
)