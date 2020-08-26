#include "basic_tower.hpp"

BasicTower::BasicTower(const TextureHolder& textures)
    : Tower(Tower::Type::Basic, textures) { 
    }


void BasicTower::CreateBullet(SceneNode& node, const TextureHolder& textures) const {
    std::unique_ptr<BasicBullet> bullet(new BasicBullet(textures));

    bullet->setPosition(GetWorldPosition());

    bullet->SetVelocity(bullet->GetSpeed() * direction_);
    std::cout << "Bullet velocity: " << bullet->GetVelocity().x << ", " << bullet->GetVelocity().y << std::endl;
    node.AttachChild(std::move(bullet));
}
