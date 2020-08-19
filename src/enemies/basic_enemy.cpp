#include "basic_enemy.hpp"
#include "../data_tables.hpp"
#include "../utility.hpp"

#include <iostream> //For initial debugging
#include <vector>


//Making a Fire type enemy as a basic derived class
BasicEnemy::BasicEnemy(const TextureHolder& textures, float difficultyLevel, float travelledDistance, int directionIndex)
    : Enemy(Enemy::Basic, textures, difficultyLevel, travelledDistance, directionIndex)
    { 
        //sprite_ = 
        
        showDeathAnimation_ = true;
        
        movementAnimation_.SetTexture(textures.Get(Textures::ID::Leppis)),
        movementAnimation_.SetFrameSize(sf::Vector2i(150, 175));
	    movementAnimation_.SetNumFrames(9);
	    movementAnimation_.SetDuration(sf::seconds(0.5));
        movementAnimation_.SetRepeating(true);
        sf::FloatRect animationBounds = movementAnimation_.GetLocalBounds();
        hasMovementAnimation_ = true;
        
        sprite_ = movementAnimation_.GetFirstFrame();
        sprite_.setOrigin(animationBounds.width/2.f, animationBounds.height/2.f);

        movementAnimation_.setScale(sf::Vector2f(0.5,0.5));
        sprite_.setScale(sf::Vector2f(0.5,0.5));
    }

// Basic enemy dies immediately when taking hit
void BasicEnemy::Damage(int) 
{
    Destroy();
}



