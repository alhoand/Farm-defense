#pragma once

#include "enemy.hpp"
#include "../command_queue.hpp"
#include <SFML/System/Time.hpp>

class MultiEnemy : public Enemy {

    public:
        MultiEnemy(const TextureHolder &textures, float difficultyLevel = 1.f, float travelledDistance = 0.f, int directionIndex = 0, int spawnCount = 3);
        //~TestEnemy();

        void TakeHit(int damage, unsigned int bulletType) override;

    private:
        bool CheckDestroyBehaviour(sf::Time dt, CommandQueue& commands) override;
 
        Command     spawnBasicEnemyCommand_;
        sf::Time    spawnTimer_;
        int         spawnCount_;
};

