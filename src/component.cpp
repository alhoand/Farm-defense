#include "component.hpp"

namespace GUI
{

Component::Component()
: isSelected_(false)
, isActive_(false)
, parent_(nullptr)
{
}

Component::~Component()
{
}

bool Component::IsSelected() const
{
	return isSelected_;
}

void Component::Select()
{
	isSelected_ = true;
}

void Component::Deselect()
{
	isSelected_ = false;
}

bool Component::IsActive() const
{
	return isActive_;
}

void Component::Activate()
{
	isActive_ = true;
}

void Component::Deactivate()
{
	isActive_ = false;
}

void Component::ChildOf(Component* parent) {
	this->parent_ = parent;
}

void Component::Update(sf::Time dt) {
	//Do nothing by default
}

sf::Transform Component::GetWorldTransform() const {
    sf::Transform transform = sf::Transform::Identity;
    for (const Component* cmp = this; cmp != nullptr; cmp = cmp->parent_) {
        transform = cmp->getTransform() * transform; // This accumulates the transform
    }
    return transform;
}

sf::Vector2f Component::GetWorldPosition() const 
{
    return GetWorldTransform() * sf::Vector2f();
}

}