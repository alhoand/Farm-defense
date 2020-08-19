#include "multi_enemy.hpp"
#include "basic_enemy.hpp"
#include "../data_tables.hpp"
#include "../utility.hpp"

#include <iostream> //For initial debugging
#include <vector>


//Making a leaf type enemy as a test of derived class
MultiEnemy::MultiEnemy(const TextureHolder& textures, float difficultyLevel, float travelledDistance, int directionIndex)
    : Enemy(Enemy::Multiplying, textures, difficultyLevel, travelledDistance, directionIndex)
    { 
        showDeathAnimation_ = false;
        
        movementAnimation_.SetTexture(textures.Get(Textures::ID::HamahakkiIso)),
        movementAnimation_.SetFrameSize(sf::Vector2i(200, 200));
	    movementAnimation_.SetNumFrames(9);
	    movementAnimation_.SetDuration(sf::seconds(0.5));
        movementAnimation_.SetRepeating(true);
        sf::FloatRect animationBounds = movementAnimation_.GetLocalBounds();
        hasMovementAnimation_ = true;
        
        sprite_ = movementAnimation_.GetFirstFrame();
        sprite_.setOrigin(animationBounds.width/2.f, animationBounds.height/2.f);

        movementAnimation_.setScale(sf::Vector2f(0.7,0.7));
        sprite_.setScale(sf::Vector2f(0.5,0.5));

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


void MultiEnemy::CheckDestroyBehaviour(CommandQueue& commands)
{
    commands.Push(spawnBasicEnemyCommand_);
    commands.Push(spawnBasicEnemyCommand_);
    commands.Push(spawnBasicEnemyCommand_);
}

