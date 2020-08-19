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
void BasicEnemy::Damage(int) 
{
    Destroy();
}


bool BasicEnemy::CheckDestroyBehaviour(CommandQueue& commands)
{
    // Basic enemy just dies
    return false;
}

