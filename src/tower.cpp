#include "tower.hpp"
#include "utility.hpp"

namespace {
	const std::vector<TowerData> table = InitializeTowerData();
}

//TODO delete commandqueue from parameters
Tower::Tower(Tower::Type type, const TextureHolder &textures)
    : Entity(1), 
    type_(type), 
    range_(table[type].range),
    sprite_(textures.Get(table[type].texture)), 
    direction_(),
    reloadTime_(table[type].reloadTime), 
    canShoot_(false), 
    bulletType_(table[type].bulletType), 
    countdown_(sf::Time::Zero),
    shootCommand_() 
    {
        sf::FloatRect bounds = sprite_.getLocalBounds();
        sprite_.setOrigin(bounds.width/2.f, bounds.height/2.f);
        shootCommand_.category_ = Category::Scene;
        shootCommand_.action_ = [this, &textures] (SceneNode& node, sf::Time) {
            CreateBullet(node, textures);
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


// Function for drawing the tower
// TODO: make use of direction_, rotation of the tower
void Tower::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite_, states);
}


//Update the state of the tower, should be virtual
void Tower::UpdateCurrent(sf::Time dt, CommandQueue&) {
    // std::cout << "Updating tower" <<std::endl;

    //if tower hasn't shot yet (no enemies are in range), do nothing and keep the countdown in zero
    if (countdown_ <= sf::Time::Zero && !canShoot_) {
        canShoot_ = true;
        std::cout << "It can! Hurrah! " << std::endl;
        countdown_ += sf::seconds(reloadTime_);
    } else if (countdown_ > sf::Time::Zero) {
        // std::cout << "It cannot :(" << std::endl;
        countdown_ -= dt;
    }

}

void Tower::Shoot(CommandQueue& commands, sf::Vector2f direction) {
    // std::cout << "Checking if tower can shoot" << std::endl;
    canShoot_ = false;
    direction_ = UnitVector(direction);
    std::cout << "direction in Shoot function: " << direction_.x << ", " << direction_.y << std::endl;
    commands.Push(shootCommand_);
}

unsigned int Tower::GetCategory() const {
    return Category::Tower;
}


// This sets the permission for the tower to move
// for now: this maybe is a clumsy way to achieve this
void Tower::SetMovePermission(bool permissionToMove) {

}

// Getter of permission to move
bool Tower::CanMove() const {

}

bool Tower::CanShoot() const 
{
    return canShoot_;
}

// Sets the tower moving with state=true, stops with state=false.
// Returns true if setting was succesful
bool Tower::SetMoveState(bool state) {

}

// Getter that tells if the tower is being moved by the player
bool Tower::IsMoving() const {

}

sf::FloatRect Tower::GetBoundingRect() const {
    return GetWorldTransform().transformRect(sprite_.getGlobalBounds()); 
}

float Tower::GetRange() const
{
    return range_;
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

void Tower::CreateBullet(SceneNode& node, const TextureHolder& textures) const {
    std::cout << "Creating a bullet" << std::endl;

    std::unique_ptr<Bullet> bullet(new Bullet(static_cast<Bullet::Type>(bulletType_), textures));

    sf::Vector2f offset(sprite_.getGlobalBounds().width / 2.f, sprite_.getGlobalBounds().height / 2.f);
    //sf::Vector2f velocity(0.0f, 100.0f);

    bullet->setPosition(GetWorldPosition() + offset);

    bullet->SetVelocity(bullet->GetSpeed() * direction_);
    std::cout << "Bullet velocity: " << bullet->GetVelocity().x << ", " << bullet->GetVelocity().y << std::endl;
    node.AttachChild(std::move(bullet));
}
