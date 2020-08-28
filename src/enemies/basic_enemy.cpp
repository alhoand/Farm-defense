#include "basic_enemy.hpp"
#include "../data_tables.hpp"
#include "../utility.hpp"

#include <iostream> //For initial debugging
#include <vector>


//Making a basic enemy class
BasicEnemy::BasicEnemy(const TextureHolder& textures, unsigned int difficultyLevel, float travelledDistance, int directionIndex)
    : Enemy(Enemy::Basic, textures, difficultyLevel, travelledDistance, directionIndex)
    {       
        showDeathAnimation_ = true;
        
        movementAnimation_.SetTexture(textures.Get(Textures::ID::HamahakkiIso)),
        movementAnimation_.SetFrameSize(sf::Vector2i(200, 200));
	    movementAnimation_.SetNumFrames(9);
	    movementAnimation_.SetDuration(sf::seconds(0.5));
        movementAnimation_.SetRepeating(true);
        sf::FloatRect animationBounds = movementAnimation_.GetLocalBounds();
        hasMovementAnimation_ = true;
        
        sprite_ = movementAnimation_.GetFirstFrame();
        sprite_.setOrigin(animationBounds.width/2.f, animationBounds.height/2.f);

        movementAnimation_.setScale(sf::Vector2f(0.3,0.3));
        sprite_.setScale(sf::Vector2f(0.3,0.3));
    }

// Basic enemy dies immediately when taking hit
void BasicEnemy::TakeHit(int, unsigned int)
{
    Destroy();
}

