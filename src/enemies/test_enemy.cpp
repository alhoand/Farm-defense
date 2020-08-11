#include "test_enemy.hpp"
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
TestEnemy::TestEnemy(const TextureHolder& textures, float travelledDistance, int directionIndex, float difficultyLevel)
    : Enemy(Enemy::Leaf, textures, 10, 50.f, travelledDistance, directionIndex, difficultyLevel)
    { 
        spawnFireEnemyCommand_.category_ = Category::Scene;
        spawnFireEnemyCommand_.action_ = [this, &textures] (SceneNode& node, sf::Time) 
        {
            std::cout <<"spawning a new enemy" << std::endl;
            std::unique_ptr<Enemy> newEnemy(new BasicEnemy(textures, travelledDistance_, directionIndex_, difficultyLevel_));
		    //newEnemy->setOrigin(newEnemy->GetBoundingRect().width/2, newEnemy->GetBoundingRect().height/2);
		    newEnemy->setPosition(this->GetWorldPosition());
            newEnemy->setScale(0.25f, 0.25f);
		    newEnemy->SetVelocity( UnitVector(this->GetVelocity()) * Table[Enemy::Fire].speed ); 
		    node.AttachChild(std::move(newEnemy));

        };
    }

/* TestEnemy::~TestEnemy() {
    for (auto it = Table.begin(); it != Table.end(); it++) {
        for (auto i = it->path.begin(); i != it->path.end(); i++)
        {
            delete i;
        }
    }
} */


void TestEnemy::CheckDestroyBehaviour(CommandQueue& commands)
{
    std::cout << "hello from here" << std::endl;
    commands.Push(spawnFireEnemyCommand_);
}

void TestEnemy::UpdateMovementPattern(sf::Time dt)
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

