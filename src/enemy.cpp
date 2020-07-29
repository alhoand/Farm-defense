//TODO class implementation here

#include "enemy.hpp"

// Associates enemies with the corresponding textures
// Textures are images that live on the graphics card

Textures::ID toTextureID(Enemy::Type type) {
    switch (type) {
    case Enemy::Type::Fire:
        return Textures::ID::Fire;
    case Enemy::Type::Water:
        return Textures::ID::Water;
    case Enemy::Type::Leaf:
        return Textures::ID::Leaf;
    default: 
        return Textures::ID::Fire;
    }
}
// Constructor that works with SFML
Enemy::Enemy(Enemy::Type type, const TextureHolder& textures, int hp, int speed)
         : type_(type), sprite_(textures.Get(toTextureID(type))),
            hitpoints_(hp),
            speed_(speed)  { 
        sf::FloatRect bounds = sprite_.getLocalBounds();
        sprite_.setOrigin(bounds.width/2.f, bounds.height/2.f);

}

// Default constructor with hard-coded values for hitpoints for testing
Enemy::Enemy() : type_(Enemy::Type::Fire), hitpoints_(50), speed_(50) { }


void Enemy::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite_, states);

}

//Update the state of enemy, should return something!
/* Possible cases:
* 1. enemy is alive (hp > 0) 
*   - and not at the end of the path
*   => move enemy forward (change position) 
*   - and it is at the end of the path)
    => game lost
* 2. enemy is dead (hp <= 0)
*  => return something to indicate enemy should be deleted from the game field
* TODO:
* Long lasting damage implementation
*/
void Enemy::UpdateCurrent(sf::Time dt) {

    Entity::UpdateCurrent(dt); // Apply velocity

    if (hitpoints_ > 0) {
        //move enemy or game lost
    } else {
        //indicate game field somehow that enemy is dead
    }
}

void Enemy::TakeHit(Bullet bullet) {
    // Do nothing for now 
}