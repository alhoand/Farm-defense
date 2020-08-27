#include "bulk_enemy.hpp"
#include <cmath>

BulkEnemy::BulkEnemy(const TextureHolder& textures, unsigned int difficultyLevel, float travelledDistance, int directionIndex)
    : Enemy(Enemy::Bulk, textures, difficultyLevel, travelledDistance, directionIndex)
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

        movementAnimation_.setScale(sf::Vector2f(0.4,0.4));
        sprite_.setScale(sf::Vector2f(0.4,0.4));

     }


void BulkEnemy::TakeHit(int damage, unsigned int bulletType)
{
    int finalDamage = damage;
    if (bulletType == Category::Bullet)
    {
        finalDamage = std::ceil(damage*0.5);
    }
    Damage(finalDamage);
}
