#include "basic_bullet.hpp"

BasicBullet::BasicBullet(const TextureHolder& textures)
    : Bullet(Bullet::Type::Basic, textures, 100, 10) { }