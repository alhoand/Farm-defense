#pragma once

#include "tower.hpp"
#include "super_bullet.hpp"

/* This is a super tower that
 * - shoots super bullets which cost 5 hp for the enemy
 * - is fast, shoots in every 0.5 seconds
 * - has a pretty good range, 250 units
*/

class SuperTower : public Tower {
    public:
        // Constructor
        SuperTower(const TextureHolder& textures);

    private:
        void CreateBullet(SceneNode& node, const TextureHolder& textures) const;
};