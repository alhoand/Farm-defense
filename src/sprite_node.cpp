#include "sprite_node.hpp"

SpriteNode::SpriteNode(const sf::Texture& texture)
        : sprite_(texture), category_(Category::None) { }

SpriteNode::SpriteNode(const sf::Texture& texture, sf::IntRect &textureRect)
                : sprite_(texture, textureRect), category_(Category::None) { }

void SpriteNode::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite_, states);
}

sf::FloatRect SpriteNode::GetBoundingRect() const
{
    if (category_ != Category::None) // Meaning we have given it a category
    {
        sf::Transform transform = GetWorldTransform();//getTransform();
        return transform.transformRect(sprite_.getGlobalBounds()); 
    }else{
        return SceneNode::GetBoundingRect();
    }
}

void SpriteNode::SetCategory(unsigned int category)
{
    category_ = category;
}

unsigned int SpriteNode::GetCategory() const
{
    if (category_ != Category::None) // Meaning we have given it a category
    {
        //std::cout << "category: " << category_ << std::endl;
        return category_;//SceneNode::GetCategory();
    }else{
        return SceneNode::GetCategory();
    }
    /*else
    {
        //std::cout << "Only scene node category" << std::endl;

        return 
    }*/
}


sf::FloatRect SpriteNode::GetBounds() const {
    return sprite_.getGlobalBounds();
}


void SpriteNode::Update(sf::Time)
{
    //Do nothing
}