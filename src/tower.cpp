//TODO class implementation here
#include "tower.hpp"

Tower::Tower(Tower::Type type, const TextureHolder &textures, int range, int reloadTime, Bullet::Type bulletType, CommandQueue& commands)
    : Entity(1), type_(type), sprite_(textures.Get(ToTextureID(type))), range_(range), direction_(0),
      reloadTime_(reloadTime), bulletType_(bulletType), countdown_(sf::Time::Zero), commands_(commands), shootCommand_() {
        shootCommand_.category_ = Category::Scene | Category::Bullet;
        shootCommand_.action_ = [this, &textures] (SceneNode& node, sf::Time) {
            std::cout << "Trying to execute commands" << std::endl;
            CreateBullet(node, Bullet::Type::FireBullet, 200.f, 200.f, textures);
        };
    }

// Default constructor with hard-coded values for hitpoints and bullet for testing
//Tower::Tower() : type_(Tower::Type::Fire), range_(5), bullet_(Bullet::Type::FireBullet,  5, 5) { }

// Destructor??

void Tower::CreateBullet(SceneNode& node, Bullet::Type type, float xOffset, float yOffset, const TextureHolder& textures) const {
    std::cout << "Creating a bullet" << std::endl;

    std::unique_ptr<Bullet> bullet(new Bullet(type, textures));

    sf::Vector2f offset(xOffset * sprite_.getGlobalBounds().width, yOffset * sprite_.getGlobalBounds().height);
    sf::Vector2f velocity(0, 50.f);

    bullet->setPosition(GetWorldPosition() + offset);
    bullet->SetVelocity(velocity);
    node.AttachChild(std::move(bullet));
}

//Update the state of the tower, should be virtual
void Tower::UpdateCurrent(sf::Time dt) {
    // std::cout << "Updating tower" <<std::endl;
    Shoot(dt);
    Entity::UpdateCurrent(dt);
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