add_subdirectory(enemies)
add_subdirectory(towers)

target_sources(TowerDefense
    PRIVATE
        resource_identifiers.hpp
        entity.hpp
        entity.cpp
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
        resource_holder.hpp
        scene_node.hpp
        scene_node.cpp
        sprite_node.hpp
        sprite_node.cpp
        
)