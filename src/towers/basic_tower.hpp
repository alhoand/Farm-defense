#pragma once

#include "tower.hpp"
#include "basic_bullet.hpp"

/* This is a basic tower that
 * - shoots basic bullets which cost 10 hp for the enemy
 * - is moderately fast, shoots in every 2 seconds
 * - has a pretty good range, 400 units
*/

class BasicTower : public Tower {
    public:
        // Constructor
        BasicTower(const TextureHolder& textures);

    private:
        void CreateBullet(SceneNode& node, const TextureHolder& textures) const;
};