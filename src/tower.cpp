//TODO class implementation here
#include <tower.hpp>

// Associates enemies with the corresponding textures
// Textures are images that live on the graphics card

Textures::ID toTextureID(Tower::Type type) {
    switch (type) {
    case Tower::Type::Fire:
        return Textures::ID::Fire;
    case Tower::Type::Water:
        return Textures::ID::Water;
    case Tower::Type::Leaf:
        return Textures::ID::Leaf;
    default: 
        return Textures::ID::Fire;
    }
}
// Constructor that works with SFML
Tower::Tower(Type type, const TextureHolder &textures, Position position, int range, int reload_speed, Bullet bullet)
         : type_(type), sprite_(textures.Get(toTextureID(type))), position_(position), range_(range),
            reload_speed_(reload_speed), bullet_(bullet) { 
        sf::FloatRect bounds = sprite_.getLocalBounds();
        sprite_.setOrigin(bounds.width/2.f, bounds.height/2.f);
}

// Default constructor with hard-coded values for hitpoints for testing
// Tower::Tower() : type_(Tower::Type::Fire) { }


void Tower::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite_, states);
}

void Tower::UpdateCurrent(sf::Time dt) {
    // what's the logic here?
}