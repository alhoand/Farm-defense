#include "bombing_tower.hpp"

BombingTower::BombingTower(const TextureHolder& textures) 
    : Tower(Tower::Type::Bombing, textures) { }


void BombingTower::CreateBullet(SceneNode& node, const TextureHolder& textures) const {
    std::unique_ptr<Bomb> bomb(new Bomb(textures));

    bomb->setPosition(GetWorldPosition());

    bomb->SetVelocity(bomb->GetSpeed() * direction_);
    node.AttachChild(std::move(bomb));
}