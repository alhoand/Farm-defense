#include "enemy.hpp"
#include "../utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <iostream> //For initial debugging
#include <cmath>

// Associates enemies with the corresponding textures
// Textures are images that live on the graphics card

namespace
{
	const std::vector<EnemyData> Table = InitializeEnemyData();
    const std::vector<Direction> Path = InitializeEnemyPath();
}
/*
Textures::ID Enemy::ToTextureID(Enemy::Type type) {
    switch (type) {
        case Enemy::Type::Fire:
            return Textures::ID::Fire;
        case Enemy::Type::Water:
            return Textures::ID::Water;
        case Enemy::Type::Leaf:
            return Textures::ID::Leaf;
        default: 
            return Textures::ID::Fire;
    }
}*/

// Constructor that works with SFML
Enemy::Enemy(Enemy::Type type, const TextureHolder& textures, unsigned int difficultyLevel, float travelledDistance, int directionIndex)
    : Entity(Table[type].hitpoints),
        type_(type), 
        //sprite_(textures.Get(ToTextureID(type))),
        sprite_(textures.Get(Textures::ID::NoTexture)),
        deathAnimation_(textures.Get(Textures::DeathAnimation)),
        movementAnimation_(),
        travelledDistance_(travelledDistance), 
        directionIndex_(directionIndex),
        difficultyLevel_(difficultyLevel),
        difficultyIncrement_(0.2), //initial, can be initialized as parameter in future
        maxSpeed_(Table[type].speed),
        isSlowedDown_(false),
        slowDownRate_(Table[type].slowDownRate), 
        isMarkedForRemoval_(false),
        hasMovementAnimation_(false),
        showDeathAnimation_(true)
    { 
        sf::FloatRect bounds = sprite_.getLocalBounds();
        sprite_.setOrigin(bounds.width/2.f, bounds.height/2.f);

        deathAnimation_.SetFrameSize(sf::Vector2i(187, 201));
	    deathAnimation_.SetNumFrames(15);
	    deathAnimation_.SetDuration(sf::seconds(0.35));
        //sf::FloatRect deathAnimationBounds = deathAnimation_.GetLocalBounds();
        //deathAnimation_.setOrigin(deathAnimationBounds.width/2.f, deathAnimationBounds.height/2.f);

    }

Enemy::~Enemy() {}

void Enemy::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
	if (IsDestroyed() && showDeathAnimation_)
		target.draw(deathAnimation_, states);
	else if (movementAnimation_.GetNumFrames() > 0)
		target.draw(movementAnimation_, states);
    else
        target.draw(sprite_, states);
}   


//Update the state of enemy
/* Possible cases:
* 1. enemy is alive (hp > 0) 
*   - and not at the end of the path
*   => move enemy forward (change position) 
*   - and it is at the end of the path)
    => game lost
* 2. enemy is dead (hp <= 0)
*  => return something to indicate enemy should be deleted from the game field
* TODO:
* Long lasting damage implementation
*/
void Enemy::UpdateCurrent(sf::Time dt, CommandQueue& commands) {

    if (IsDestroyed())
	{
		
        deathAnimation_.Update(dt);
		if((deathAnimation_.IsFinished() || !showDeathAnimation_)){
            CheckDestroyBehaviour(commands);
            isMarkedForRemoval_ = true;
        }
        
        
		return;
	}
    UpdateMovementAnimation(dt);
    UpdateMovementPattern(dt);
    Entity::UpdateCurrent(dt, commands); 
}

void Enemy::CheckDestroyBehaviour(CommandQueue&)
{
    // By default do nothing, but different types may have some action here
}

unsigned int Enemy::GetCategory() const 
{
    if(IsDestroyed())
        return 0;
    return Category::Enemy;
} 

sf::FloatRect Enemy::GetBoundingRect() const
{
	return GetWorldTransform().transformRect(sprite_.getGlobalBounds());
}


//Enemy movement pattern
void Enemy::UpdateMovementPattern(sf::Time dt)
{
	if (!Path.empty())
	{
		if (travelledDistance_ > Path[directionIndex_].distance)
		{
			directionIndex_ = (directionIndex_ + 1) % Path.size();
			travelledDistance_ = 0.f;
            sprite_.setRotation(Path[directionIndex_].angle); //kääntää enemyn hitboxin animaation alla kun suuntaa muuttuu, jos rikkoo jotain ni pois vaan
		}
        
		float radians = ToRadian(Path[directionIndex_].angle); 
		float vx = GetSpeed() * std::cos(radians);
		float vy = GetSpeed() * std::sin(radians);

		SetVelocity(vx, vy); //entity function

		travelledDistance_ += GetSpeed() * dt.asSeconds();

        isSlowedDown_ = false; // if enemy was slowed down, return to not slowed down state
	}

} 

void Enemy::UpdateMovementAnimation(sf::Time dt){
    if(hasMovementAnimation_){
        //sf::Vector2f vel = GetVelocity();
        //int rotation = atan(-vel.x/vel.y)*57.29577+90; //*57.29577 to convert rad -> deg
        //movementAnimation_.Update(dt,rotation);
        //jos tää menee rikki ni sen saa taas toimii noilla ylemmillä riveillä
        movementAnimation_.Update(dt,Path[directionIndex_].angle);
    }
}

// initialized false, can be changed in derived classes
bool Enemy::IsMarkedForRemoval() const {
    return isMarkedForRemoval_;// && (deathAnimation_.IsFinished() || !showDeathAnimation_));
}

// Enemy's speed increases by DifficultyCoefficient
float Enemy::GetSpeed() const
{
    if (isSlowedDown_)
    {
        return slowDownRate_ * DifficultyCoefficient() * maxSpeed_; 
    } 
    return DifficultyCoefficient() * maxSpeed_;
}

void Enemy::SlowDown() 
{
    isSlowedDown_ = true;
}

// Default case, can be altered in derived classes and take into account the bullet category
void Enemy::TakeHit(Bullet& bullet)
{
    switch(bullet.GetCategory()) {
        case Category::SlowingBullet :
            SlowDown();
        default:
            Damage(bullet.GetDamage());
    }
}


float Enemy::DifficultyCoefficient() const
{
    return 1 + difficultyLevel_*difficultyIncrement_;
}