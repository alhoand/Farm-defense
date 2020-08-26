#include "bombing_tower.hpp"

BombingTower::BombingTower(const TextureHolder& textures) 
    : Tower(Tower::Type::Bombing, textures, 150, 8) { }


void BombingTower::CreateBullet(SceneNode& node, const TextureHolder& textures) const {
    std::unique_ptr<Bomb> bomb(new Bomb(textures));

    bomb->setPosition(GetWorldPosition());

    bomb->SetVelocity(bomb->GetSpeed() * direction_);
    std::cout << "Bomb velocity: " << bomb->GetVelocity().x << ", " << bomb->GetVelocity().y << std::endl;
    node.AttachChild(std::move(bomb));
}