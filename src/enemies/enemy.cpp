#include "enemy.hpp"
#include "../utility.hpp"
#include "../data_tables.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <iostream> //For initial debugging
#include <cmath>

// Associates enemies with the corresponding textures
// Textures are images that live on the graphics card

//this function should be in data_tables.cpp
/*
std::vector<EnemyData> initializeEnemyData()
{
    std::cout << "DEBUG: Initializing enemy data" << std::endl; 

	std::vector<EnemyData> data(Enemy::TypeCount);

	data[Enemy::Fire].hitpoints = 50;
	data[Enemy::Fire].speed = 50.f;
	data[Enemy::Fire].texture = Textures::Fire;
	data[Enemy::Fire].path.push_back(Direction(0.f, 400.f));
	data[Enemy::Fire].path.push_back(Direction(+90.f, 200.f));
	data[Enemy::Fire].path.push_back(Direction(0.f, 400.f));
    data[Enemy::Fire].path.push_back(Direction(-90.f, 200.f));

    data[Enemy::Leaf].hitpoints = 50;
	data[Enemy::Leaf].speed = 50.f;
	data[Enemy::Leaf].texture = Textures::Fire;
	data[Enemy::Leaf].path.push_back(Direction(0.f, 400.f));
	data[Enemy::Leaf].path.push_back(Direction(+90.f, 200.f));
	data[Enemy::Leaf].path.push_back(Direction(0.f, 400.f));
    data[Enemy::Leaf].path.push_back(Direction(-90.f, 200.f));


	return data;
}*/

//should work like this but doesn't
namespace
{
	const std::vector<EnemyData> Table = InitializeEnemyData();
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
Enemy::Enemy(Enemy::Type type, const TextureHolder& textures, int hp, int speed)
    : Entity(hp),
        type_(type), 
        sprite_(textures.Get(ToTextureID(type))),
        travelledDistance_(0.f), 
        directionIndex_(0),
        speed_(speed)
    { 
        sf::FloatRect bounds = sprite_.getLocalBounds();
        sprite_.setOrigin(bounds.width/2.f, bounds.height/2.f);
    }


// Default constructor with hard-coded values for hitpoints for testing
Enemy::Enemy() : Entity(50), type_(Enemy::Type::Fire), speed_(50) { }


void Enemy::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite_, states);
}


//Update the state of enemy, should return something!
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
void Enemy::UpdateCurrent(sf::Time dt) {
 // Apply velocity

    if (GetHitpoints() > 0) 
    {
        //move enemy or game lost
        UpdateMovementPattern(dt);
        Entity::UpdateCurrent(dt); 
    } else {
        //indicate game field somehow that enemy is dead
    }
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
	const std::vector<Direction>& path = Table[type_].path;

	if (!path.empty())
	{
		if (travelledDistance_ > path[directionIndex_].distance)
		{
			directionIndex_ = (directionIndex_ + 1) % path.size();
			travelledDistance_ = 0.f;
		}

		float radians = toRadian(path[directionIndex_].angle); 
		float vx = speed_ * std::cos(radians);
		float vy = speed_ * std::sin(radians);

		SetVelocity(vx, vy); //entity function

		travelledDistance_ += speed_ * dt.asSeconds();
	}

}