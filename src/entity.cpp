#include "entity.hpp"

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

// Makes the entity move with sfml move function
void Entity::UpdateCurrent(sf::Time dt) {
    move(velocity_ * dt.asSeconds());
}