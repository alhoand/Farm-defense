#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "scene_node.hpp"

// Represents sprites that only need to be rendered on screen, not updated or moved
// Used to represent background tiles
class SpriteNode : public SceneNode {
public:
    SpriteNode(const sf::Texture& texture);
    SpriteNode(const sf::Texture& texture, sf::IntRect& rect);


private:
    virtual void   DrawCurrent(sf::RenderTarget& target,sf::RenderStates states) const;
    sf::Sprite sprite_;
    
};