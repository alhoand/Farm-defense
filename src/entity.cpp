#include "entity.hpp"

Entity::Entity(int hp) : hitpoints_(hp) {}

void Entity::SetVelocity(sf::Vector2f velocity) {
    velocity_ = velocity;
}

void Entity::SetVelocity(float vx, float vy) {
    velocity_.x = vx;
    velocity_.y = vy;
}

sf::Vector2f Entity::GetVelocity() const {
    return velocity_;
}

int Entity::GetHitpoints() const
{
    return hitpoints_;
}

// Makes the entity move with sfml move function
void Entity::UpdateCurrent(sf::Time dt, CommandQueue&) {
    move(velocity_ * dt.asSeconds());
}

void Entity::Destroy() 
{
    hitpoints_ = 0;
}

bool Entity::IsDestroyed() const
{
    return hitpoints_ <= 0;
}

void Entity::Damage(int damage) 
{
    hitpoints_ -= damage;
}
