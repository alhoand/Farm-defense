#include "slowing_tower.hpp"

SlowingTower::SlowingTower(const TextureHolder& textures)
    : Tower(Tower::Type::Slowing, textures, 600, 3) { }


void SlowingTower::CreateBullet(SceneNode& node, const TextureHolder& textures) const {
    std::unique_ptr<SlowingBullet> bullet(new SlowingBullet(textures));

    bullet->setPosition(GetWorldPosition());

    bullet->SetVelocity(bullet->GetSpeed() * direction_);
    std::cout << "Bullet velocity: " << bullet->GetVelocity().x << ", " << bullet->GetVelocity().y << std::endl;
    node.AttachChild(std::move(bullet));
}