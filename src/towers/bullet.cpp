#include "bullet.hpp"

#include "../resource_holder.hpp"
#include "../category.hpp"
#include "../data_tables.hpp"

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
      damage_(table[type].damage), 
      damage_duration_(table[type].damageDuration) {
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

unsigned int Bullet::GetCategory() const
{
    unsigned int type;
    switch (type_)
    {
        case Bullet::FireBullet :
            type = Category::FireBullet;
            break;
        case Bullet::WoodBullet :
            type = Category::WoodBullet;
            break;
        case Bullet::IceBullet :
            type = Category::IceBullet;
            break;
        default:
            type = Category::FireBullet;
            break;
    }
	return type;
}
