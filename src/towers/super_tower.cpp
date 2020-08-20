#include "super_tower.hpp"

SuperTower::SuperTower(const TextureHolder& textures)
    : Tower(Tower::Type::Super, textures, 400, 0.5) { }


void SuperTower::CreateBullet(SceneNode& node, const TextureHolder& textures) const {
    std::unique_ptr<SuperBullet> bullet(new SuperBullet(textures));

    bullet->setPosition(GetWorldPosition());

    bullet->SetVelocity(bullet->GetSpeed() * direction_);
    std::cout << "Bullet velocity: " << bullet->GetVelocity().x << ", " << bullet->GetVelocity().y << std::endl;
    node.AttachChild(std::move(bullet));
}