#include "bomb.hpp"

Bomb::Bomb(const TextureHolder& textures) 
    : Bullet(Bullet::Type::Bomb, textures, 100, 10), 
      distance_(150), 
      range_(100), 
      travelledDistance_(0),
      detonateCommand_(),
      isDetonated_(false) { 
        // Initialize detonateCommand_
        // Category is Enemy, since the command will be executed for all enemies in range
        detonateCommand_.category_ = Category::Enemy;
        detonateCommand_.action_ = DerivedAction<Enemy>([this] (Enemy& enemy, sf::Time) {
            // If the enemy is in range, it will take a hit
            if (Distance(*this, enemy) <= range_) {
                enemy.TakeHit(this->GetDamage());
            }
        });
    }

// Getter for bomb's range
int Bomb::GetRange() {
    return range_;
}

// Boolean to indicate whether the bomb has been detonated
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

// Detonate function tells the bomb to detonate, that is, push detonate command to command queue
void Bomb::Detonate(CommandQueue& commands) {
    // Set boolean to true, so that we can destroy it in GameField later
    isDetonated_ = true;
    commands.Push(detonateCommand_);
}
