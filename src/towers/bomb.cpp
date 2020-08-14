#include "bomb.hpp"

Bomb::Bomb(const TextureHolder& textures) 
    : Bullet(Bullet::Type::Bomb, textures, 150, 10), 
      distance_(150), 
      range_(200), 
      travelledDistance_(0),
      detonateCommand_(),
      isDetonated_(false) { 
        detonateCommand_.category_ = Category::Enemy;
        detonateCommand_.action_ = DerivedAction<Enemy>([this] (Enemy& enemy, sf::Time) {
            if (Distance(*this, enemy) <= range_) {
                std::cout << "Bomb detonated!" << std::endl;
                enemy.Damage(this->GetHitpoints());
            }
        });
    }

int Bomb::GetRange() {
    return range_;
}

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

void Bomb::Detonate(CommandQueue& commands) {
    isDetonated_ = true;
    commands.Push(detonateCommand_);
    // Destroy();
}
