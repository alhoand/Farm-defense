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

Tower::Tower(Tower::Type type, const TextureHolder &textures, Position p)
        : type_(Type::Fire), sprite_(textures.Get(ToTextureID(type))),  canMove_(true), isMoving_(false), position_(p) { }

// Default constructor with hard-coded values for hitpoints for testing
Tower::Tower() : type_(Tower::Type::Fire), canMove_(true), isMoving_(false), position_(0, 0) { }

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

bool Tower::SetMoveState(bool state) {
    if (canMove_) {
        isMoving_ = state;
        return true;
    }else{
        return false;
    }
}

bool Tower::IsMoving() const {
    return isMoving_;
}

sf::FloatRect Tower::GetBoundingRect() const {
    return GetWorldTransform().transformRect(sprite_.getGlobalBounds()); 
}