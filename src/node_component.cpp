#include "node_component.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{
SceneNodeComponent::SceneNodeComponent(SceneNode*) : node_(nullptr) {
    std::cout << "A new sceneNodeComponent created" << std::endl;
 }

bool SceneNodeComponent::IsSelectable() const
{
    return false;
}

void SceneNodeComponent::HandleEvent(const sf::Event&)
{
}

void SceneNodeComponent::Draw(sf::RenderTarget&, sf::RenderStates) const
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