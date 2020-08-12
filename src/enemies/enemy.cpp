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
}

// Constructor that works with SFML
Enemy::Enemy(Enemy::Type type, const TextureHolder& textures, float difficultyLevel, float travelledDistance, int directionIndex)
    : Entity(Table[type].hitpoints),
        type_(type), 
        //sprite_(textures.Get(ToTextureID(type))),
        sprite_(textures.Get(Textures::ID::NoTexture)),
        travelledDistance_(travelledDistance), 
        directionIndex_(directionIndex),
        difficultyLevel_(difficultyLevel),
        speed_(Table[type].speed),
        isMarkedForRemoval_(false)
        //dataTable_(Table)
    { 
        sf::FloatRect bounds = sprite_.getLocalBounds();
        sprite_.setOrigin(bounds.width/2.f, bounds.height/2.f);
    }

Enemy::~Enemy() {}

void Enemy::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
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
		CheckDestroyBehaviour(commands);

		isMarkedForRemoval_ = true;
		return;
	}
    UpdateMovementPattern(dt);
    Entity::UpdateCurrent(dt, commands); 
}

void Enemy::CheckDestroyBehaviour(CommandQueue&)
{
    // By default do nothing, but different types may have some action here
}

unsigned int Enemy::GetCategory() const 
{
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
		}

		float radians = ToRadian(Path[directionIndex_].angle); 
		float vx = speed_ * std::cos(radians);
		float vy = speed_ * std::sin(radians);

		SetVelocity(vx, vy); //entity function

		travelledDistance_ += speed_ * dt.asSeconds();
	}

} 

// initialized false, can be changed later
bool Enemy::IsMarkedForRemoval() const {
    return isMarkedForRemoval_;
}

float Enemy::GetSpeed() const
{
    return speed_;
}