#include "scene_node.hpp"
#include "command.hpp"
#include "command_queue.hpp"
#include "utility.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <cassert>
#include <set>
#include <algorithm>

SceneNode::SceneNode(Category::Type category) : children_(), parent_(nullptr), defaultCategory_(category) { }

void SceneNode::AttachChild(Ptr node) {
    node->parent_ = this;
    children_.push_back(std::move(node));

}

void SceneNode::Update(sf::Time dt, CommandQueue& commands) {
    UpdateCurrent(dt, commands);
    UpdateChildren(dt, commands);
}

void SceneNode::UpdateCurrent(sf::Time, CommandQueue&) {
    //do nothing
}

void SceneNode::UpdateChildren(sf::Time dt, CommandQueue& commands) {
    for (Ptr &child : children_) {
        child->Update(dt, commands);
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
sf::Vector2f SceneNode::GetWorldPosition() const 
{
    return GetWorldTransform() * sf::Vector2f();
}


void SceneNode::CheckNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs)
{
	if (this != &node && Collision(*this, node) && !IsDestroyed() && !node.IsDestroyed())
    {
		collisionPairs.insert(std::minmax(this, &node));
    }

	for(Ptr& child : children_)
    {
        child->CheckNodeCollision(node, collisionPairs);
    }		
}

void SceneNode::CheckSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs)
{
	CheckNodeCollision(sceneGraph, collisionPairs);

	for(Ptr& child : sceneGraph.children_)
    {
        CheckSceneCollision(*child, collisionPairs);
    }
		
}

bool SceneNode::IsDestroyed() const 
{   
    //default case
    return false;
}

//some other cases than immediate death?
bool SceneNode::IsMarkedForRemoval() const
{
    return IsDestroyed();
}

void SceneNode::RemoveWrecks()
{
    auto wreckfieldBegin = std::remove_if(children_.begin(),children_.end(), std::mem_fn(&SceneNode::IsMarkedForRemoval));
    children_.erase(wreckfieldBegin, children_.end());

    std::for_each(children_.begin(), children_.end(),std::mem_fn(&SceneNode::RemoveWrecks));
}

sf::FloatRect SceneNode::GetBoundingRect() const 
{
    return sf::FloatRect();
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

    DrawBoundingRect(target, states);
}

void SceneNode::DrawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    // Do nothing by default
}

void SceneNode::DrawChildren(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const Ptr &child : children_) {
        child->Draw(target, states);
    }
}


//
unsigned int SceneNode::GetCategory() const {
    return defaultCategory_; // By default every scene node belongs to Scene-category
}

// From the sfml game development -book
void SceneNode::OnCommand(const Command &command, sf::Time dt) {
    // This works because all non-zero values are cast to true
    // e.g.
    // 0010 & 0010 -> 0010 = 2 = true
    // 1101 & 0100 -> 0100 = 4 = true 
    // 1000 & 0100 -> 0000 = 0 = false
    if (command.category_ & GetCategory()) { 
        command.action_(*this, dt);
        //this->accelerate(2.f, 3.f);
    } 
        for (const Ptr &child : children_) {
            child->OnCommand(command, dt);
        }
}


void SceneNode::DrawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const
{
	sf::FloatRect rect = GetBoundingRect();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);

	target.draw(shape);
}


bool Collision(const SceneNode& lhs, const SceneNode& rhs) 
{
    return lhs.GetBoundingRect()
              .intersects(rhs.GetBoundingRect());
}


float Distance(const SceneNode& lhs, const SceneNode& rhs)
{
	return Length(lhs.GetWorldPosition() - rhs.GetWorldPosition());
}

