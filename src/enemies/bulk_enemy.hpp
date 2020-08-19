#pragma once

#include "enemy.hpp"

class BulkEnemy : public Enemy {

    public:
        BulkEnemy(const TextureHolder &textures, float difficultyLevel = 1.f, float travelledDistance = 0.f, int directionIndex = 0);
        //~BasicEnemy();        

    private:
        //bool CheckDestroyBehaviour(CommandQueue& commands) override;
};