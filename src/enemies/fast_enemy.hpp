#pragma once

#include "enemy.hpp"
#include "../category.hpp"

class FastEnemy : public Enemy {

    public:
        FastEnemy(const TextureHolder &textures, unsigned int difficultyLevel = 1, float travelledDistance = 0.f, int directionIndex = 0);
        
        void TakeHit(int damage, unsigned int bulletType);
};