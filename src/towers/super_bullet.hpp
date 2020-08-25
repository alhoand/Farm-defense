#pragma once

#include "bullet.hpp"

/* This is a super bullet, shot by super towers, that
 * - has damage of 5 hp
 * - has speed of 200
 */

class SuperBullet : public Bullet {
    public:
        SuperBullet(const TextureHolder& textures)
            : Bullet(Bullet::Type::Super, textures, 200, 5) { }
};