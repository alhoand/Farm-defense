#include "ghost.hpp"
#include "tower.hpp"

Ghost::Ghost(Tower::Type type, TextureHolder& textures, sf::Vector2f sideBarPos) : SpriteNode(textures.Get(Tower::ToTextureID(type))), sideBarPos_(sideBarPos), isDragged_(false), active_(false)
 {  }


void Ghost::GetBack() {
    setPosition(sideBarPos_);
    SetTransparent();
}

unsigned int Ghost::GetCategory() const {
    return Category::Ghost;
}

sf::Vector2f Ghost::GetPosition() const {
    sf::Transform transform = getTransform();
    return transform * sf::Vector2f();
}

void Ghost::Drag() {
    sprite_.setColor(sf::Color(255, 255, 255, 128));
    isDragged_ = true;
}

void Ghost::UnDrag() {
    isDragged_ = false;
}
bool Ghost::IsDragged() const {
    return isDragged_;
}

sf::Vector2f Ghost::GetSideBarPos() const {
    return sideBarPos_;
}


sf::FloatRect Ghost::GetBoundingRect() const {
    sf::Transform transform = getTransform();
    return transform.transformRect(sprite_.getGlobalBounds()); 
}


void Ghost::SetTransparent() {
    sprite_.setColor(sf::Color(255, 255, 255, 0)); //transparent
/*    sf::CircleShape range;
    range.setFillColor(sf::Color(255, 0, 0, 128));
    range.setOrigin(range.getLocalBounds().width/2.f, range.getLocalBounds().height);
    range.setPosition(getPosition()); */
}


void Ghost::SetVisible() {
    sprite_.setColor(sf::Color(255, 255, 255, 255));
}