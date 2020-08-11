//TODO class implementation here
#include "tower.hpp"
#include <cassert>
namespace {
	const std::vector<TowerData> table = InitializeTowerData();
}

Tower* Tower::activeTower_  = nullptr;

void Tower::ActiveTower(Tower* newActive) 
{ 
    assert(newActive != nullptr); 
    activeTower_ = newActive;
}

Tower::Tower(Tower::Type type, const TextureHolder &textures, int range, int reloadTime, Bullet::Type bulletType, CommandQueue& commands)
    : Entity(1), type_(type), sprite_(textures.Get(ToTextureID(type))), range_(range),
      reloadTime_(reloadTime), bulletType_(bulletType), countdown_(sf::Time::Zero), commands_(commands), shootCommand_() {
        shootCommand_.category_ = Category::Scene;
        shootCommand_.action_ = [this, &textures] (SceneNode& node, sf::Time) {
            CreateBullet(node, Bullet::Type::FireBullet, textures);
        };
    }

/*Tower::Tower(Tower::Type type, const TextureHolder &textures, CommandQueue& commands)
    : Entity(1), type_(type), 
      sprite_(textures.Get(ToTextureID(type))), 
      range_(table[type].range),
      reloadTime_(table[type].reloadTime), 
      bulletType_(table[type].bulletType),
      countdown_(sf::Time::Zero), 
      commands_(commands), 
      shootCommand_() {
        shootCommand_.category_ = Category::Scene;
        shootCommand_.action_ = [this, &textures] (SceneNode& node, sf::Time) {
            CreateBullet(node, Bullet::Type::FireBullet, textures);
        };
    }*/

// Default constructor with hard-coded values for hitpoints and bullet for testing
//Tower::Tower() : type_(Tower::Type::Fire), range_(5), bullet_(Bullet::Type::FireBullet,  5, 5) { }

// Destructor??

void Tower::CreateBullet(SceneNode& node, Bullet::Type type, const TextureHolder& textures) const {
    std::cout << "Creating a bullet" << std::endl;

    std::unique_ptr<Bullet> bullet(new Bullet(type, textures));

    sf::Vector2f offset(sprite_.getGlobalBounds().width / 2.f, sprite_.getGlobalBounds().height / 2.f);
    sf::Vector2f velocity(0.0f, 100.0f);

    bullet->setPosition(GetWorldPosition() + offset);
    bullet->SetVelocity(velocity); // direction_ * bullet->GetSpeed());
    node.AttachChild(std::move(bullet));
}

//Update the state of the tower, should be virtual
void Tower::UpdateCurrent(sf::Time dt) {
    // std::cout << "Updating tower" <<std::endl;
    Shoot(dt);
    // Entity::UpdateCurrent(dt);
}

void Tower::Shoot(sf::Time dt) {
    // std::cout << "Checking if tower can shoot" << std::endl;
    if (countdown_ <= sf::Time::Zero) {
        commands_.Push(shootCommand_);
        std::cout << "It can! Hurrah! " << std::endl;
        countdown_ += sf::seconds(1.f * reloadTime_);
    } else if (countdown_ > sf::Time::Zero) {
        // std::cout << "It cannot :(" << std::endl;
        countdown_ -= dt;
    }
}

// This sets the permission for the tower to move
// for now: this maybe is a clumsy way to achieve this
void Tower::SetMovePermission(bool permissionToMove) {

}

// Getter of permission to move
bool Tower::CanMove() const {

}

// Sets the tower moving with state=true, stops with state=false.
// Returns true if setting was succesful
bool Tower::SetMoveState(bool state) {

}

// Getter that tells if the tower is being moved by the player
bool Tower::IsMoving() const {

}

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