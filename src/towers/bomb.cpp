#include "bomb.hpp"

Bomb::Bomb(const TextureHolder& textures) 
    : Bullet(Bullet::Type::Bomb, textures, 100, 10), 
      distance_(150), 
      range_(100), 
      travelledDistance_(0),
      detonateCommand_(),
      canDetonate_(false)
      { }

// Getter for bomb's range
int Bomb::GetRange() {
    return range_;
}

// Tells (i.e. for game field) if bomb can detonate of not
bool Bomb::CanDetonate()
{
    return canDetonate_;
}


void Bomb::UpdateCurrent(sf::Time dt, CommandQueue& ) {
    if (travelledDistance_ >= distance_) {
        canDetonate_ = true;
        return;
    }
    travelledDistance_ += GetSpeed() * dt.asSeconds();
    Entity::UpdateCurrent(dt, commands);
}

