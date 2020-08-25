#pragma once

#include "bullet.hpp"

/* This is a basic bullet, shot by basic towers, that
 * - has damage of 10 hp
 * - has speed of 150
 */

class BasicBullet : public Bullet {
    public:
        BasicBullet(const TextureHolder& textures)
            : Bullet(Bullet::Type::Basic, textures, 150, 10) { }
};