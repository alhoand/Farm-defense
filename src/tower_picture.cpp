#include "tower_picture.hpp"

TowerPicture::TowerPicture(Tower::Type type, TextureHolder& textures, sf::Vector2f sideBarPos) : SpriteNode(textures.Get(Tower::ToTextureID(type))), sideBarPos_(sideBarPos), isDragged_(false), active_(false)
 {  }


void TowerPicture::GetBack() {
    setPosition(sideBarPos_);
    SetTransparent();
}

unsigned int TowerPicture::GetCategory() const {
    return Category::TowerPicture;
}

sf::Vector2f TowerPicture::GetPosition() const {
    sf::Transform transform = getTransform();
    return transform * sf::Vector2f();
}

void TowerPicture::Drag() {
    sprite_.setColor(sf::Color(255, 255, 255, 128));
    isDragged_ = true;
}

void TowerPicture::UnDrag() {
    isDragged_ = false;
}
bool TowerPicture::IsDragged() const {
    return isDragged_;
}

sf::Vector2f TowerPicture::GetSideBarPos() const {
    return sideBarPos_;
}


sf::FloatRect TowerPicture::GetBoundingRect() const {
    sf::Transform transform = getTransform();
    return transform.transformRect(sprite_.getGlobalBounds()); 
}


void TowerPicture::SetTransparent() {
    sprite_.setColor(sf::Color(255, 255, 255, 0)); //transparent
/*    sf::CircleShape range;
    range.setFillColor(sf::Color(255, 0, 0, 128));
    range.setOrigin(range.getLocalBounds().width/2.f, range.getLocalBounds().height);
    range.setPosition(getPosition()); */
}


void TowerPicture::SetVisible() {
    sprite_.setColor(sf::Color(255, 255, 255, 255));
}