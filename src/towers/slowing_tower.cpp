#include "slowing_tower.hpp"

SlowingTower::SlowingTower(const TextureHolder& textures)
    : Tower(Tower::Type::Slowing, textures, 400, 0) { }


void SlowingTower::CreateBullet(SceneNode& node, const TextureHolder& textures) const {
    // Do nothing
}