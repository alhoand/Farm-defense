#include "slowing_tower.hpp"

SlowingTower::SlowingTower(const TextureHolder& textures)
    : Tower(Tower::Type::Slowing, textures, 300, 0) { }