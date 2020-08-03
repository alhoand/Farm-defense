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

Tower::Tower(Tower::Type type, const TextureHolder &textures, Position p, int range, int reload_speed, Bullet bullet)
        : type_(Type::Fire),
            sprite_(textures.Get(ToTextureID(type))), 
            range_(range),
            canMove_(true),
            isMoving_(false),
            position_(p),
            reload_speed_(reload_speed),
            bullet_(bullet) { }

// Default constructor with hard-coded values for hitpoints and bullet for testing
Tower::Tower() : type_(Tower::Type::Fire), range_(5), canMove_(true), isMoving_(false), position_(0, 0), bullet_(BulletType::Fire, Position(0, 0), 5, 5) { }

unsigned int Tower::GetCategory() const {
    return Category::Tower;
}

void Tower::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite_, states);
}

    // Sets the permission for the tower to move
void Tower::SetMovePermission(bool permissionToMove) {
    canMove_ = permissionToMove;
}
    
    // Getter of permission to move
bool Tower::CanMove() const {
    return canMove_;
}

// Returns true if changing the state was successful
bool Tower::SetMoveState(bool state) {
    if (canMove_ && (IsMoving() != state)) {
        isMoving_ = state;
        return true;
    } else if (!canMove_ && (IsMoving() != state)) {
        isMoving_ = state;
        return false;
    } else {
        return false;
    }
}

bool Tower::IsMoving() const {
    return isMoving_;
}

sf::FloatRect Tower::GetBoundingRect() const {
    return GetWorldTransform().transformRect(sprite_.getGlobalBounds()); 
}