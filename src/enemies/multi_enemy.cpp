#include "multi_enemy.hpp"
#include "basic_enemy.hpp"
#include "../data_tables.hpp"
#include "../utility.hpp"

#include <iostream> //For initial debugging
#include <vector>


//Making a leaf type enemy as a test of derived class
MultiEnemy::MultiEnemy(const TextureHolder& textures, float difficultyLevel, float travelledDistance, int directionIndex, int spawnCount)
    : Enemy(Enemy::Multiplying, textures, difficultyLevel, travelledDistance, directionIndex), spawnTimer_(sf::Time::Zero), spawnCount_(spawnCount)
    { 
        showDeathAnimation_ = false;
        spawnBasicEnemyCommand_.category_ = Category::Scene;
        spawnBasicEnemyCommand_.action_ = [this, &textures] (SceneNode& node, sf::Time) 
        {
            std::cout <<"spawning a new enemy" << std::endl;
            std::unique_ptr<Enemy> newEnemy(new BasicEnemy(textures, difficultyLevel_, travelledDistance_, directionIndex_));
		    newEnemy->setPosition(this->GetWorldPosition());
            //newEnemy->setScale(0.25f, 0.25f);
		    newEnemy->SetVelocity( UnitVector(this->GetVelocity()) * newEnemy->GetSpeed() ); 
		    node.AttachChild(std::move(newEnemy));
        };
    }


bool MultiEnemy::CheckDestroyBehaviour(sf::Time dt, CommandQueue& commands)
{
    if (spawnCount_ > 0)
    {
        if (spawnTimer_ <= sf::Time::Zero)
        {
            std::cout << "spawning a basic enemy" << std::endl;
            commands.Push(spawnBasicEnemyCommand_);

            spawnCount_--;
            spawnTimer_ = sf::seconds(0.1);
        } else
        {
            spawnTimer_ -= dt;
        }
        return true;
    } 
    // destroy behaviour is finished, can be removed now
    return false;
}

