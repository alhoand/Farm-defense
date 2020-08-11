#include "basic_enemy.hpp"
#include "../data_tables.hpp"
#include "../utility.hpp"

#include <iostream> //For initial debugging
#include <vector>

namespace
{
	const std::vector<EnemyData> Table = InitializeEnemyData();
}


//Making a leaf type enemy as a test of derived class
BasicEnemy::BasicEnemy(const TextureHolder& textures, float travelledDistance, int directionIndex, float difficultyLevel)
    : Enemy(Enemy::Fire, textures, 50, 50.f, travelledDistance, directionIndex, difficultyLevel)
    { 
    }



void BasicEnemy::CheckDestroyBehaviour(CommandQueue& commands)
{
    // Basic enemy just dies
}

void BasicEnemy::UpdateMovementPattern(sf::Time dt)
{
	const std::vector<Direction>& path = Table[type_].path;

	if (!path.empty())
	{
		if (travelledDistance_ > path[directionIndex_].distance)
		{
			directionIndex_ = (directionIndex_ + 1) % path.size();
			travelledDistance_ = 0.f;
		}

		float radians = ToRadian(path[directionIndex_].angle); 
		float vx = speed_ * std::cos(radians);
		float vy = speed_ * std::sin(radians);

		SetVelocity(vx, vy); //entity function

		travelledDistance_ += speed_ * dt.asSeconds();
	}

}



