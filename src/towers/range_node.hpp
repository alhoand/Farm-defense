#pragma once
#include "../scene_node.hpp"

class RangeNode : public SceneNode {
    friend void             DrawRange(const RangeNode& rangeNode, sf::RenderTarget& target, sf::RenderStates states);

    public:
                            RangeNode(float radius, sf::Color color);

        void                SetRadius(float radius);

        void                SetColor(sf::Color color);
        void                SetDefaultColor(sf::Color color);
        float               GetRadius() const;
        void                SetDefaultColor();
    private:
    
        virtual void        DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

        float               radius_;
        sf::Color           color_;
        sf::Color           defaultColor_;
        sf::CircleShape     circle_;

};

void    DrawRange(const RangeNode& rangeNode, sf::RenderTarget& target, sf::RenderStates states);