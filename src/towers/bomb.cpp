#include "bomb.hpp"

Bomb::Bomb(const TextureHolder& textures) 
    : Bullet(Bullet::Type::Bomb, textures, 100, 10), 
      distance_(150), 
      range_(100), 
      travelledDistance_(0),
      detonateCommand_(),
     // isDetonated_(false),
      canDetonate_(false)
      { }

// Getter for the bomb's range of destruction
int Bomb::GetRange() {
    return range_;
}

bool Bomb::CanDetonate()
{
    return canDetonate_;
}

// Boolean, has the bomb been detonated?
/* bool Bomb::IsDetonated() {
    return isDetonated_;
} */

void Bomb::UpdateCurrent(sf::Time dt, CommandQueue& commands) {
    if (travelledDistance_ >= distance_) {
        canDetonate_ = true;
        return;
    }
    travelledDistance_ += GetSpeed() * dt.asSeconds();
    Entity::UpdateCurrent(dt, commands);
}

// Pushes detonate command to command queue
/* void Bomb::Detonate(CommandQueue& commands) {
    isDetonated_ = true;
    //commands.Push(detonateCommand_);
} */
