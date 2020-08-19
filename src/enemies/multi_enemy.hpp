#pragma once

#include "enemy.hpp"
#include "../command_queue.hpp"

class MultiEnemy : public Enemy {

    public:
        MultiEnemy(const TextureHolder &textures, float difficultyLevel = 1.f, float travelledDistance = 0.f, int directionIndex = 0);
        //~TestEnemy();

    private:
        void CheckDestroyBehaviour(CommandQueue& commands) override;
 
        Command spawnBasicEnemyCommand_;
};

