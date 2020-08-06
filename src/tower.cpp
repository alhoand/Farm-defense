//TODO class implementation here
#include "tower.hpp"

Textures::ID Tower::ToTextureID(Tower::Type type) {
    switch (type) {
        case Tower::Type::Fire:
            return Textures::ID::FireTower;
        case Tower::Type::Water:
            return Textures::ID::WaterTower;
        case Tower::Type::Leaf:
            return Textures::ID::LeafTower;
        default: 
            return Textures::ID::Fire;
    }
}

Tower::Tower(Tower::Type type, const TextureHolder &textures, int range, int reload_speed, Bullet::Type bullet_type)
        : type_(Type::Fire),
            sprite_(textures.Get(ToTextureID(type))), 
            range_(range),
            reload_speed_(reload_speed),
            bulletType_(bullet_type) { }

// Default constructor with hard-coded values for hitpoints and bullet for testing
//Tower::Tower() : type_(Tower::Type::Fire), range_(5), bullet_(Bullet::Type::FireBullet,  5, 5) { }

unsigned int Tower::GetCategory() const {
    return Category::Tower;
}

// Function for drawing the tower
// TODO: make use of direction_, rotation of the tower
void Tower::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite_, states);
}

sf::FloatRect Tower::GetBoundingRect() const {
    return GetWorldTransform().transformRect(sprite_.getGlobalBounds()); 
}