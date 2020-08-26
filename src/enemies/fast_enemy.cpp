#include "fast_enemy.hpp"
#include <cmath>

FastEnemy::FastEnemy(const TextureHolder& textures, float difficultyLevel, float travelledDistance, int directionIndex)
    : Enemy(Enemy::Fast, textures, difficultyLevel, travelledDistance, directionIndex)
    { 
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

        movementAnimation_.setScale(sf::Vector2f(0.2,0.2));
        sprite_.setScale(sf::Vector2f(0.2,0.2));
    }

// FastEnemy resists damage from basic bullets and gets more damage from bombs
void FastEnemy::TakeHit(int damage, unsigned int bulletType)
{
    int finalDamage = damage;
    if (bulletType == Category::BasicBullet)
    {
        finalDamage = std::ceil(finalDamage * 0.5);
    }
    else if (bulletType == Category::Bomb)
    {
        finalDamage = std::floor(finalDamage * 1.5);
    }
    Damage(finalDamage);
}