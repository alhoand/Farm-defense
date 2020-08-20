#include "bomb.hpp"

Bomb::Bomb(const TextureHolder& textures) 
    : Bullet(Bullet::Type::Bomb, textures, 100, 10), 
      distance_(150), 
      range_(100), 
      travelledDistance_(0),
      detonateCommand_(),
      isDetonated_(false) { 
        detonateCommand_.category_ = Category::Enemy;
        detonateCommand_.action_ = DerivedAction<Enemy>([this] (Enemy& enemy, sf::Time) {
            if (Distance(*this, enemy) <= range_) {
                enemy.TakeHit(this->GetDamage());
            }
        });
    }

// Getter for the bomb's range of destruction
int Bomb::GetRange() {
    return range_;
}

// Boolean, has the bomb been detonated?
bool Bomb::IsDetonated() {
    return isDetonated_;
}

void Bomb::UpdateCurrent(sf::Time dt, CommandQueue& commands) {
    if (travelledDistance_ >= distance_) {
        Detonate(commands);
        return;
    }
    travelledDistance_ += GetSpeed() * dt.asSeconds();
    Entity::UpdateCurrent(dt, commands);
}

// Pushes detonate command to command queue
void Bomb::Detonate(CommandQueue& commands) {
    isDetonated_ = true;
    commands.Push(detonateCommand_);
}
