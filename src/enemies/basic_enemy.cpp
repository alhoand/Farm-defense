#include "basic_enemy.hpp"
#include "../data_tables.hpp"
#include "../utility.hpp"

#include <iostream> //For initial debugging
#include <vector>


//Making a leaf type enemy as a test of derived class
BasicEnemy::BasicEnemy(const TextureHolder& textures, float difficultyLevel, float travelledDistance, int directionIndex)
    : Enemy(Enemy::Fire, textures, difficultyLevel, travelledDistance, directionIndex)
    { 
    }


void BasicEnemy::CheckDestroyBehaviour(CommandQueue& commands)
{
    // Basic enemy just dies
}

