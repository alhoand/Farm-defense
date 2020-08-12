#include "basic_enemy.hpp"
#include "../data_tables.hpp"
#include "../utility.hpp"

#include <iostream> //For initial debugging
#include <vector>


//Making a Fire type enemy as a basic derived class
BasicEnemy::BasicEnemy(const TextureHolder& textures, float difficultyLevel, float travelledDistance, int directionIndex)
    : Enemy(Enemy::Fire, textures, difficultyLevel, travelledDistance, directionIndex)
    { 
    }

// Basic enemy dies immediately when taking hit
void BasicEnemy::Damage(int) 
{
    Destroy();
}


void BasicEnemy::CheckDestroyBehaviour(CommandQueue& commands)
{
    // Basic enemy just dies
}

