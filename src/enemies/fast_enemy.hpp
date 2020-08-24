#pragma once

#include "enemy.hpp"
#include "../category.hpp"

class FastEnemy : public Enemy {

    public:
        FastEnemy(const TextureHolder &textures, float difficultyLevel = 1.f, float travelledDistance = 0.f, int directionIndex = 0);
        
        void TakeHit(int damage, unsigned int bulletType);
};