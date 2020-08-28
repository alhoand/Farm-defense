#pragma once

#include "enemy.hpp"

class BasicEnemy : public Enemy {

    public:
        BasicEnemy(const TextureHolder &textures, unsigned int difficultyLevel = 1, float travelledDistance = 0.f, int directionIndex = 0);
        //~BasicEnemy();
        
        void TakeHit(int damage, unsigned int bulletType);
};