#include "tower.hpp"

#include <math.h> 
#include <cmath> 

namespace {
	const std::vector<TowerData> table = InitializeTowerData();
}

// Constructor
Tower::Tower(Tower::Type type, const TextureHolder &textures)
    : Entity(1), 
      type_(type),
      sprite_(textures.Get(ToTextureID(type))),
      range_(table[type].range), 
      reloadTime_(table[type].reloadTime), 
      canShoot_(false), 
      countdown_(sf::Time::Zero),
      shootCommand_() {
        sf::FloatRect bounds = sprite_.getLocalBounds();
        sprite_.setOrigin(bounds.width/2.f, bounds.height/2.f);

        Tower::towerCount_++;
        // Adds a range circle for the tower according to the range of the tower attack
        std::unique_ptr<RangeNode> rangeCircle(new RangeNode(range_, sf::Color(255, 0, 0, 128)));
        rangeCircle_ = rangeCircle.get();
        AttachChild(std::move(rangeCircle));

        // Initializing shootCommand_
        // Category is Scene, since this command is executed only once in the game field
        shootCommand_.category_ = Category::Scene;
        shootCommand_.action_ = [this, &textures] (SceneNode& node, sf::Time) {
            // A bullet is created and shot
            CreateBullet(node, textures);
        };
    }
/*
Textures::ID Tower::ToTextureID(Type type)
{
    return table[type].texture;
}
*/

int Tower::towerCount_ = 0;


void Tower::ActiveTower(Tower &newActive, CommandQueue& commands)
{

    Command actCmd;
    actCmd.category_ = Category::Tower;
   // std::cout << "All cool here" << std::endl;
    actCmd.action_ = DerivedAction<Tower>([&](Tower& t, sf::Time)
    {
        if (&t == &newActive)
        {

            t.Activate();
            //std::cout << "New active tower added" << std::endl;

        }
        else
        {
            t.Deactivate();
            //std::cout << "address of t: " << &t << ", address of new: " << &newActive << std::endl;
            //std::cout << "No new active added" << std::endl;
        }
        
    });
    commands.Push(actCmd);
}

void Tower::Collides(bool collision)
{
    if (collision)
    {
        rangeCircle_->SetColor(sf::Color(255, 0, 0, 128));
        isColliding_ = true;
    }else
    {
        rangeCircle_->SetDefaultColor();
        isColliding_ = false;
    }
    
}

void Tower::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    if(IsActive())
        DrawRange(*rangeCircle_, target, states);
    target.draw(sprite_, states);
}

//Update the state of the tower
void Tower::UpdateCurrent(sf::Time dt, CommandQueue&) {
    // If tower hasn't shot yet (no enemies are in range), do nothing and do not reduce countdown
    if ((countdown_ <= sf::Time::Zero) && !IsMoving()) {
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
    /*if (type_ == Tower::Slowing) {
        return Category::SlowingTower;
    } else if (type_ == Tower::Bombing) {
        return Category::BombingTower;
    }
    return Category::ShootingTower;*/
    unsigned int myCategory = Category::Tower;

    if (type_ == Tower::Slowing)
    {
        myCategory = Category::SlowingTower;
    } else if (type_ == Tower::Bombing)
    {
        //std::cout << "Bombing tower!" << std::endl;
        myCategory =  Category::BombingTower;
    } else
    {
        myCategory = Category::ShootingTower;
    }

    if(IsActive())
    {
       // unsigned int temp = myCategory;
       // unsigned int temp2 = Category::Active;
        myCategory = Category::Active | myCategory;
        /*
        if (temp & myCategory)
            std::cout << "This works!" << std::endl;
        if (temp2 & myCategory)
           std::cout << "This works as well!" << std::endl; */
    }

    return myCategory;

}


bool Tower::MyRange(RangeNode* rangeNodePtr)
{
    return rangeCircle_ == rangeNodePtr;

}

bool Tower::IsActive() const
{
    return isActive_;
}

void Tower::Activate()
{
    isActive_ = true;
}

void Tower::Deactivate()
{
    isActive_ = false;
}

// This sets the permission for the tower to move
// for now: this maybe is a clumsy way to achieve this
void Tower::AllowMoving()
{
    canMove_ = true;
}

void Tower::DisallowMoving() 
{
    Stop();
    canMove_ = false;
}

// Getter of permission to move
bool Tower::CanMove() const
{
    return canMove_;
}

bool Tower::CanShoot() const 
{
    return canShoot_;
}

// Sets the tower moving
// Returns true if setting was succesful
bool Tower::Move()
{
    if (canMove_)
    {
        isMoving_ = true;
        MakeTransparent();
    }
        
    return canMove_;
}

void Tower::Stop()
{
    isMoving_ = false;
    MakeVisible();
}

// Getter that tells if the tower is being moved by the player.
// This is used when the player adds new towers to the game field using the GUI sidebar.
// When the tower is being placed, (i.e., moving), the tower should not for example shoot at enemies yet.
bool Tower::IsMoving() const {
    return isMoving_;
}


sf::FloatRect Tower::GetBoundingRect() const {
    return GetWorldTransform().transformRect(sprite_.getGlobalBounds()); 
}

float Tower::GetRange() const {
    return range_;
}

//Makes the tower invisible
void Tower::MakeTransparent() {
    sprite_.setColor(sf::Color(255, 255, 255, 0));
}

//Sets the opacity to maximum. This function can be used to make the tower visible again.
// This is now used to make the placement / addition of towers from GUI with mouse.
// For more info, check out Tower::IsMoving()
void Tower::MakeVisible() 
{
    sprite_.setColor(sf::Color(255, 255, 255, 255));
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
