#include "bullet.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>

namespace {
	const std::vector<BulletData> table = InitializeBulletData();
}

Bullet::Bullet(Type type, const TextureHolder& textures)
    : Entity(1),
      type_(type), 
      sprite_(textures.Get(table[type].texture)),
      speed_(table[type].speed), 
      damage_(table[type].damage) {
        sf::FloatRect bounds = sprite_.getLocalBounds();
        sprite_.setOrigin(bounds.width/2.f, bounds.height/2.f);
    }

float Bullet::GetSpeed() const {
    return speed_;
}

int Bullet::GetDamage() const {
    return damage_;
}

unsigned int Bullet::GetCategory() const {
    unsigned int type;
    switch (type_) {
        case Bullet::Basic :
            type = Category::BasicBullet;
            break;
        case Bullet::Super :
            type = Category::SuperBullet;
            break;
        case Bullet::Bomb :
            type = Category::Bomb;
            break;
        default:
            type = Category::BasicBullet;
            break;
    }
	return type;
}

sf::FloatRect Bullet::GetBoundingRect() const {
	return GetWorldTransform().transformRect(sprite_.getGlobalBounds());
}

void Bullet::UpdateCurrent(sf::Time dt,CommandQueue& commands) {
    Entity::UpdateCurrent(dt, commands);
}

void Bullet::DrawCurrent(sf::RenderTarget& target,sf::RenderStates states) const {
    target.draw(sprite_, states);
}