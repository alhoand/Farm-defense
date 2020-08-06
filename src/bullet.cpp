#include "bullet.hpp"
#include "entity.hpp"
#include "resource_holder.hpp"
#include "category.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>

Textures::ID Bullet::ToTextureID(Bullet::Type type) {
    switch (type) {
        case Bullet::Type::Ice:
            return Textures::ID::Ice;
        case Bullet::Type::FireBullet:
            return Textures::ID::FireBullet;
        case Bullet::Type::Wood:
            return Textures::ID::Wood;
        default: 
            return Textures::ID::Ice;
    }
}

Bullet::Bullet(Type type, int damage, int damage_duration, const TextureHolder& textures)
    : Entity(1),
        type_(type), 
        sprite_(textures.Get(ToTextureID(type))),
        targetDirection_(),
        damage_(damage),
        damage_duration_(damage_duration)
    {
        sf::FloatRect bounds = sprite_.getLocalBounds();
        sprite_.setOrigin(bounds.width/2.f, bounds.height/2.f);
    }

Bullet::Bullet(Type type, const TextureHolder& textures)
    : type_(type), sprite_(textures.Get(ToTextureID(type))), targetDirection_(),
      damage_(), damage_duration_() {
        sf::FloatRect bounds = sprite_.getLocalBounds();
        sprite_.setOrigin(bounds.width/2.f, bounds.height/2.f);
    }

        //could also return damage duration, depends on how the hit to enemy is implemented
int Bullet::GetDamage() const {
    return damage_;
}

sf::FloatRect Bullet::GetBoundingRect() const 
{
	return GetWorldTransform().transformRect(sprite_.getGlobalBounds());
}

void Bullet::UpdateCurrent(sf::Time dt)
{
    Entity::UpdateCurrent(dt);
}

void Bullet::DrawCurrent(sf::RenderTarget& target,sf::RenderStates states) const
{
    target.draw(sprite_, states);
}

unsigned int Bullet::GetCategory() const
{
	return Category::Bullet;
}
