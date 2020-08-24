#include "tower.hpp"

#include <math.h> 
#include <cmath> 

// Constructor
Tower::Tower(Tower::Type type, const TextureHolder &textures, float range, float reloadTime)
    : Entity(1), 
      type_(type),
      sprite_(textures.Get(ToTextureID(type))),
      range_(range), 
      reloadTime_(reloadTime), 
      canShoot_(false), 
      countdown_(sf::Time::Zero),
      shootCommand_() {
        sf::FloatRect bounds = sprite_.getLocalBounds();
        sprite_.setOrigin(bounds.width/2.f, bounds.height/2.f);
        // Initializing shootCommand_
        // Category is Scene, since this command is executed only once in the game field
        shootCommand_.category_ = Category::Scene;
        shootCommand_.action_ = [this, &textures] (SceneNode& node, sf::Time) {
            // A bullet is created and shot
            CreateBullet(node, textures);
        };
    }

void Tower::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite_, states);
}

//Update the state of the tower
void Tower::UpdateCurrent(sf::Time dt, CommandQueue&) {
    // If tower hasn't shot yet (no enemies are in range), do nothing and do not reduce countdown
    if (countdown_ <= sf::Time::Zero) {
        canShoot_ = true;
        //std::cout << "It can! Hurrah! " << std::endl;
        countdown_ += sf::seconds(reloadTime_);
    } else if (countdown_ > sf::Time::Zero  && !canShoot_) {
        // std::cout << "It cannot :(" << std::endl;
        countdown_ -= dt;
    }
}

void Tower::Shoot(CommandQueue& commands, sf::Vector2f direction) {
    canShoot_ = false;
    direction_ = UnitVector(direction);
    if(direction.x < 0)
        sprite_.setRotation(atan(direction.y/direction.x)*57);
    else
        sprite_.setRotation(atan(direction.y/direction.x)*57+180);
    commands.Push(shootCommand_);
}


unsigned int Tower::GetCategory() const {
    if (type_ == Tower::Slowing) {
        return Category::SlowingTower;
    } else if (type_ == Tower::Bombing) {
        return Category::BombingTower;
    }
    return Category::ShootingTower;
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

float Tower::GetRange() const {
    return range_;
}

//This will be pure virtual, is not needed here
/*void Tower::CreateBullet(SceneNode& node, const TextureHolder& textures) const {
    std::cout << "Creating a bullet" << std::endl;

    std::unique_ptr<Bullet> bullet(new Bullet(static_cast<Bullet::Type>(bulletType_), textures));

    //sf::Vector2f offset(sprite_.getGlobalBounds().width / 2.f, sprite_.getGlobalBounds().height / 2.f);
    //sf::Vector2f velocity(0.0f, 100.0f);

    bullet->setPosition(GetWorldPosition());

    bullet->SetVelocity(bullet->GetSpeed() * direction_);
    std::cout << "Bullet velocity: " << bullet->GetVelocity().x << ", " << bullet->GetVelocity().y << std::endl;
    node.AttachChild(std::move(bullet));
}*/

Textures::ID Tower::ToTextureID(Tower::Type type) {
    switch (type) {
        case Tower::Type::Basic:
            return Textures::ID::BasicTower;
        case Tower::Type::Slowing:
            return Textures::ID::SlowingTower;
        case Tower::Type::Super:
            return Textures::ID::SuperTower;
        case Tower::Type::Bombing:
            return Textures::ID::BombingTower;
        default: 
            return Textures::ID::NoTexture;
    }
}