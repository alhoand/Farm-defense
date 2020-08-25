#pragma once

#include "enemy.hpp"
#include "../command_queue.hpp"

class TestEnemy : public Enemy {

    public:
        TestEnemy(const TextureHolder& textures, float difficultyLevel = 1.f, float travelledDistance = 0.f, int directionIndex = 0);
        //~TestEnemy();

    private:
        bool CheckDestroyBehaviour(sf::Time, CommandQueue& commands) override;
 
        Command spawnFireEnemyCommand_;
};

