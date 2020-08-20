#pragma once

#include "tower.hpp"
#include "bomb.hpp"

/* This is a bombing tower that
 * - shoots bombs which cost 10 hp for any enemy in range
 * - is pretty slow, shoots in every 8 seconds
 * - has a medium range, 200 units
*/

class BombingTower : public Tower {
    public:
        BombingTower(const TextureHolder& textures);

    private:
        void CreateBullet(SceneNode& node, const TextureHolder& textures) const;
};