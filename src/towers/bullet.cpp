#include "bullet.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>

/*Bullet::Bullet(Type type, const TextureHolder& textures)
    : Entity(1),
      type_(type), 
      sprite_(textures.Get(ToTextureID(type))),
      speed_(table[type].speed), 
      damage_(table[type].damage), 
      damageDuration_(table[type].damageDuration) {
        sf::FloatRect bounds = sprite_.getLocalBounds();
        sprite_.setOrigin(bounds.width/2.f, bounds.height/2.f);
    }*/

// Constructor to be used with inherited classes
Bullet::Bullet(Type type, const TextureHolder& textures, float speed, int damage, int damageDuration)
    : Entity(1),
      type_(type), 
      sprite_(textures.Get(ToTextureID(type))),
      speed_(speed), 
      damage_(damage), 
      damageDuration_(damageDuration) {
        sf::FloatRect bounds = sprite_.getLocalBounds();
        sprite_.setOrigin(bounds.width/2.f, bounds.height/2.f);
    }

float Bullet::GetSpeed() const {
    return speed_;
}

        //could also return damage duration, depends on how the hit to enemy is implemented
int Bullet::GetDamage() const {
    return damage_;
}

sf::FloatRect Bullet::GetBoundingRect() const 
{
	return GetWorldTransform().transformRect(sprite_.getGlobalBounds());
}

void Bullet::UpdateCurrent(sf::Time dt,CommandQueue& commands)
{
    Entity::UpdateCurrent(dt, commands);
}

void Bullet::DrawCurrent(sf::RenderTarget& target,sf::RenderStates states) const
{
    target.draw(sprite_, states);
}

unsigned int Bullet::GetCategory() const {
    unsigned int type;
    switch (type_) {
        case Bullet::Basic :
            type = Category::BasicBullet;
            break;
        case Bullet::Slowing :
            type = Category::SlowingBullet;
            break;
        case Bullet::Super :
            type = Category::SuperBullet;
            break;
        default:
            type = Category::BasicBullet;
            break;
    }
	return type;
}

Textures::ID Bullet::ToTextureID(Bullet::Type type) {
    switch (type) {
        case Bullet::Type::Basic:
            return Textures::ID::BasicBullet;
        case Bullet::Type::Slowing:
            return Textures::ID::SlowingBullet;
        case Bullet::Type::Super:
            return Textures::ID::SuperBullet;
        default: 
            return Textures::ID::BasicBullet;
    }
}