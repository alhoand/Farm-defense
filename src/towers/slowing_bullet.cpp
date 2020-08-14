#include "slowing_bullet.hpp"

SlowingBullet::SlowingBullet(const TextureHolder& textures)
    : Bullet(Bullet::Type::Slowing, textures, 150, 10, 1) { }