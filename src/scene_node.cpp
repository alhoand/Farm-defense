#include "scene_node.hpp"

SceneNode::SceneNode() : children_(), parent_(nullptr) { }

void SceneNode::AttachChild(Ptr node) {
    node->parent_ = this;
    children_.push_back(std::move(node));

}

void SceneNode::Update(sf::Time dt) {
    UpdateCurrent(dt);
    UpdateChildren(dt);
}

void SceneNode::UpdateCurrent(sf::Time dt) {
    //do nothing
}

void SceneNode::UpdateChildren(sf::Time dt) {
    for (Ptr &child : children_) {
        child->Update(dt);
    }
}

// Iterative version
sf::Transform SceneNode::GetWorldTransform() const {
    sf::Transform transform = sf::Transform::Identity;
    for (const SceneNode* node = this; node != nullptr; node = node->parent_) {
        transform = node->getTransform() * transform; // This accumulates the transform
    }
    return transform;
}


// The absolute position of the SceneNode in the game field
sf::Vector2f SceneNode::GetWorldPosition() const {
    return GetWorldTransform() * sf::Vector2f();
}


SceneNode::Ptr SceneNode::DetachChild(const SceneNode& node) {
    auto found = std::find_if(children_.begin(), children_.end(), 
        [&] (Ptr &p) {
            return p.get() == &node;
        });
    assert(found != children_.end()); 
    Ptr result = std::move(*found); // result takes ownership of the child
    result->parent_ = nullptr; // makes the child's parent a nullptr
    children_.erase(found); // removes the child from its parent
    return result; // result is 
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    Draw(target, states);
}

void SceneNode::Draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    DrawCurrent(target, states);
    DrawChildren(target, states);
}

void SceneNode::DrawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    // Do nothing by default
}

void SceneNode::DrawChildren(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const Ptr &child : children_) {
        child->Draw(target, states);
    }
}


