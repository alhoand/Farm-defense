//enemy class implementation

#include "enemy.hpp"
#include "data_tables.hpp"
#include "utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <iostream> //For initial debugging
#include <cmath>

// Associates enemies with the corresponding textures
// Textures are images that live on the graphics card

//this function should be in data_tables.cpp
std::vector<EnemyData> initializeEnemyData()
{
    //DEBUG

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
}

//should work like this but doesn't
namespace
{
	const std::vector<EnemyData> Table = initializeEnemyData();
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
    : type_(type), 
        sprite_(textures.Get(ToTextureID(type))),
        travelledDistance_(0.f), 
        directionIndex_(0),
        hitpoints_(hp),
        speed_(speed)
    { 
        sf::FloatRect bounds = sprite_.getLocalBounds();
        sprite_.setOrigin(bounds.width/2.f, bounds.height/2.f);
    }


// Default constructor with hard-coded values for hitpoints for testing
Enemy::Enemy() : type_(Enemy::Type::Fire), hitpoints_(50), speed_(50) { }


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

    std::cout << "Updating enemy" <<std::endl;
    updateMovementPattern(dt);
    Entity::UpdateCurrent(dt); // Apply velocity

    if (hitpoints_ > 0) {
        //move enemy or game lost
    } else {
        //indicate game field somehow that enemy is dead
    }
}

void Enemy::TakeHit(Bullet bullet) 
{
    std::cout << bullet.GetDamage() << std::endl;
    // Do nothing for now 
}

unsigned int Enemy::GetCategory() const 
{
    return Category::Enemy;
} 

sf::FloatRect Enemy::getBoundingRect() const
{
	return GetWorldTransform().transformRect(sprite_.getGlobalBounds());
}

//Enemy movement pattern
void Enemy::updateMovementPattern(sf::Time dt)
{
    std::cout << "DEBUG: updating enemy movement pattern" << std::endl;

	const std::vector<Direction>& path = Table[type_].path;

	if (!path.empty())
	{
		if (travelledDistance_ > path[directionIndex_].distance)
		{
            std::cout << "changing direction" << std::endl;
			directionIndex_ = (directionIndex_ + 1) % path.size();
			travelledDistance_ = 0.f;
		}
        std::cout << "DEBUG:" << directionIndex_ << ", " << travelledDistance_ << std::endl;

		float radians = toRadian(path[directionIndex_].angle); // helper function toRadian?
		float vx = speed_ * std::cos(radians);
		float vy = speed_ * std::sin(radians);

		SetVelocity(vx, vy); //entity

		travelledDistance_ += speed_ * dt.asSeconds();
	}

    std::cout << "Checking velocity after update" << GetVelocity().x << "," << GetVelocity().y << std::endl;
}