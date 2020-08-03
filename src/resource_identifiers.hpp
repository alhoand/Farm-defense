#pragma once
#include "resource_holder.hpp"
namespace sf {
    class Texture;
    class Font;
}

namespace Textures {
    enum class ID {
        Fire,
        Leaf,
        Water,
        Grass,
        FireTower,
        WaterTower,
        LeafTower,
        Path,
        TitleBackground
    };
}

namespace Fonts {
    enum class ID {
        Title,
        Main,
        Game
    };
}

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder; 

typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;