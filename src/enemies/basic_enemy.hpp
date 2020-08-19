#pragma once

#include "enemy.hpp"

class BasicEnemy : public Enemy {

    public:
        BasicEnemy(const TextureHolder &textures, float difficultyLevel = 1.f, float travelledDistance = 0.f, int directionIndex = 0);
        //~BasicEnemy();
        void Damage(int damage) override;
        

    private:
        void CheckDestroyBehaviour(CommandQueue& commands) override;
};