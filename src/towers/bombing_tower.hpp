#pragma once

#include "tower.hpp"
#include "bomb.hpp"

class BombingTower : public Tower {
    public:
        BombingTower(const TextureHolder& textures);

    private:
        void CreateBullet(SceneNode& node, const TextureHolder& textures) const;
};