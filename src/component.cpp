#include "component.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "container.hpp"


namespace GUI
{

Component::Component()
: type_(GUI::ID::Default)
, isSelected_(false)
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

void Component::Update(sf::Time) {
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
/*
void Component::DrawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::FloatRect rect = GetGlobalBounds();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);

	target.draw(shape);
}
*/

/*GUI::Component* Component::GetParent() const {
	return parent_;
}*/

GUI::ID Component::GetType() const {
	return type_;
}

void Component::SetType(GUI::ID type) {
	type_ = type;
}

}