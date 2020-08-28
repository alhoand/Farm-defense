#include "multi_enemy.hpp"
#include "basic_enemy.hpp"
#include "../data_tables.hpp"
#include "../utility.hpp"

#include <iostream> //For initial debugging
#include <vector>


MultiEnemy::MultiEnemy(const TextureHolder& textures, unsigned int difficultyLevel, float travelledDistance, int directionIndex, int spawnCount)
    : Enemy(Enemy::Multiplying, textures, difficultyLevel, travelledDistance, directionIndex), spawnTimer_(sf::Time::Zero), spawnCount_(spawnCount)
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
            //std::cout <<"spawning a new enemy" << std::endl;
            std::unique_ptr<Enemy> newEnemy(new BasicEnemy(textures, difficultyLevel_, travelledDistance_, directionIndex_));
		    newEnemy->setPosition(this->GetWorldPosition());
		    newEnemy->SetVelocity( UnitVector(this->GetVelocity()) * newEnemy->GetSpeed() ); 
		    node.AttachChild(std::move(newEnemy));
        };
    }

//If dies after taking damage from bomb, doubles spawncount
void MultiEnemy::TakeHit(int damage, unsigned int bulletType)
{
    Damage(damage);
    if (bulletType == Category::Bomb && IsDestroyed())
    {
        spawnCount_ *= 2;
    }
}


bool MultiEnemy::CheckDestroyBehaviour(sf::Time dt, CommandQueue& commands)
{
    if (spawnCount_ > 0)
    {
        if (spawnTimer_ <= sf::Time::Zero)
        {
            //std::cout << "spawning a basic enemy" << std::endl;
            commands.Push(spawnBasicEnemyCommand_);

            spawnCount_--;
            spawnTimer_ = sf::seconds(0.3);
        } else
        {
            spawnTimer_ -= dt;
        }
        return true;
    } 
    // destroy behaviour is finished, can be removed now
    return false;
}
