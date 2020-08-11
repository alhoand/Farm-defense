#include "node_component.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

SceneNodeComponent::SceneNodeComponent(SceneNode* node) :
node_(nullptr)
{
}

bool SceneNodeComponent::IsSelectable() const
{
    return false;
}


void SceneNodeComponent::HandleEvent(const sf::Event&)
{
}

void SceneNodeComponent::Draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void SceneNodeComponent::SetNode(SceneNode* node)
{
	node_ = node;
}

SceneNode* SceneNodeComponent::GetNode() const {
    return node_;
}

}