#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "scene_node.hpp"

// Represents sprites that only need to be rendered on screen, not updated or moved
// Used to represent background tiles
class SpriteNode : public SceneNode {
    public:
                            SpriteNode(const sf::Texture& texture);
                            SpriteNode(const sf::Texture& texture, sf::IntRect& rect);
        sf::FloatRect       GetBounds() const;
        virtual void        Update(sf::Time);
        void                SetCategory(unsigned int category);
        unsigned int        GetCategory() const override;
        sf::FloatRect       GetBoundingRect() const override;


    protected:
        virtual void        DrawCurrent(sf::RenderTarget& target,sf::RenderStates states) const;
        sf::Sprite          sprite_;
        unsigned int        category_;
    
};