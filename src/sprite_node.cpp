#include "sprite_node.hpp"

SpriteNode::SpriteNode(const sf::Texture& texture)
        : sprite_(texture), category_(0) { }

SpriteNode::SpriteNode(const sf::Texture& texture, sf::IntRect &textureRect)
                : sprite_(texture, textureRect) { }

void SpriteNode::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite_, states);
}
sf::FloatRect SpriteNode::GetBoundingRect() const
{
    if (category_)
    {
        sf::Transform transform = GetWorldTransform();//getTransform();
        return transform.transformRect(sprite_.getGlobalBounds()); 
    }else{
        SceneNode::GetBoundingRect();
    }
}
void SpriteNode::SetCategory(unsigned int category)
{
    category_ = category;
}

unsigned int SpriteNode::GetCategory() const
{
    if (category_)
    {
        return category_;
    }
    else
    {
        return SceneNode::GetCategory();
    }
}


sf::FloatRect SpriteNode::GetBounds() const {
    return sprite_.getGlobalBounds();
}


void SpriteNode::Update(sf::Time)
{
    //Do nothing
}