#pragma once

#include "tower.hpp"
#include "basic_bullet.hpp"

/* This is a basic tower that
 * - shoots basic bullets which cost one hp for the enemy
 * - is moderately fast
 * - has a medium range
*/

class BasicTower : public Tower {
    public:
        // Constructor
        BasicTower(const TextureHolder& textures);


    private:
        void CreateBullet(SceneNode& node, const TextureHolder& textures) const;
};