#include "range_node.hpp"
#include "../utility.hpp"

RangeNode::RangeNode(float range, sf::Color color) :
radius_(range)
, color_(color)
, circle_(radius_)
{
    circle_.setFillColor(sf::Color(0, 0, 0, 128));
    circle_.setOrigin(circle_.getLocalBounds().width/2.f, circle_.getLocalBounds().height/2.f);
}

void RangeNode::SetColor(sf::Color color)
{
    circle_.setFillColor(color);
    color_ = color;
}

void RangeNode::SetRadius(float radius)
{
    circle_.setRadius(radius);
    
    radius_ = radius;
}

float RangeNode::GetRadius() const
{
    return radius_;
}

void RangeNode::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    //target.draw(circle_, states);
}


void DrawRange(const RangeNode& rangeNode, sf::RenderTarget& target, sf::RenderStates states)
{
    target.draw(rangeNode.circle_, states);
}

