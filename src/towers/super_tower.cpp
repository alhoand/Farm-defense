#include "super_tower.hpp"

SuperTower::SuperTower(const TextureHolder& textures)
    : Tower(Tower::Type::Super, textures) {}


void SuperTower::CreateBullet(SceneNode& node, const TextureHolder& textures) const {
    std::unique_ptr<SuperBullet> bullet(new SuperBullet(textures));

    bullet->setPosition(GetWorldPosition());

    bullet->SetVelocity(bullet->GetSpeed() * direction_);
    node.AttachChild(std::move(bullet));
}