#pragma once
#include "resource_holder.hpp"
namespace sf {
    class Texture;
}


namespace Textures {
    enum class ID {
        Fire,
        Leaf,
        Water,
        Grass,
        Path
    };
}

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder; 