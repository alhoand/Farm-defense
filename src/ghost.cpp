#include "ghost.hpp"
#include "tower.hpp"

Ghost::Ghost(Tower::Type type, TextureHolder& textures, sf::Vector2f sideBarPos) : SpriteNode(textures.Get(Tower::ToTextureID(type))), sideBarPos_(sideBarPos), clicked_(false)
 { sprite_.setPosition(sideBarPos_); }


void Ghost::GetBack() {
    setPosition(sideBarPos_);
}

unsigned int Ghost::GetCategory() const {
    return Category::Ghost;
}

sf::Vector2f Ghost::GetPosition() const {
    return sprite_.getPosition();
}
void Ghost::SetClicked(bool value) {
    clicked_ = value;
}
bool Ghost::GetClicked() const{
    return clicked_;
}

