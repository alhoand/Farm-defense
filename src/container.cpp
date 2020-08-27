#include "container.hpp"
//#include <foreach.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <cassert>
#include <memory>
#include <iostream>

namespace GUI
{

Container::Container()
: children_()
, selectedChild_(-1)
, velocity_()
{
}

void Container::Pack(Component::Ptr component, bool relativeTo)
{
	if(relativeTo)
	{
		component->FollowerOf(this); //Stores the container as the parent
	}
	
	children_.push_back(component);
}
/*
std::shared_ptr<GUI::Button> Container::GetButton(GUI::ID type) {
	auto found = std::find_if(children_.begin(), children_.end(),
		[&] (Ptr& child) {
			return child.get()->GetType() == type;
	});
	assert(found != children_.end());
	return std::dynamic_pointer_cast<GUI::Button>(*found);
}*/


Component::Ptr Container::GetChild(GUI::ID type) {
	auto found = std::find_if(children_.begin(), children_.end(),
		[&] (GUI::Component::Ptr& child) {
			return child.get()->GetType() == type;
	});
	assert(found != children_.end());
	return *found;
}




bool Container::IsSelectable() const
{
    return false;
}

void Container::Draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

	for(const Component::Ptr& child: children_) 
	{
		if(child->IsFollowerOf(this))
			target.draw(*child, states);
		else
		{
			target.draw(*child); // Do not take the parent's states into consideration
		}
		
		
		//GUI::Component::DrawBoundingRect(target, states);			
	}
		
	
}

void Container::Update(sf::Time dt) {
	UpdateCurrent(dt);
	UpdateChildren(dt);
}

void Container::UpdateCurrent(sf::Time dt) {
	move(velocity_ * dt.asSeconds());
}

void Container::UpdateChildren(sf::Time dt)
{
	for(const Component::Ptr& child: children_){
		child->Update(dt);
	}
		
}

bool Container::HandleEvent(const sf::Event& event)
{
	if(event.type == sf::Event::MouseMoved){
		int n = 0;
		for(const Component::Ptr& child: children_){
			if(child->GetGlobalBounds().contains(sf::Vector2f(event.mouseMove.x,event.mouseMove.y))){
				selectedChild_ = n;
				child->Select();	
				return true; // Propagate events
			}
			else
			{
				child->Deselect();
			}
			n++;
		}
		selectedChild_ = -1;
	}
	else if(event.type == sf::Event::MouseButtonPressed){
		int n = 0;
		for(const Component::Ptr& child: children_){
			if(child->GetGlobalBounds().contains(sf::Vector2f(event.mouseButton.x,event.mouseButton.y))){
				selectedChild_ = n;
				if (children_[selectedChild_]->IsSelected())
				{
					//std::cout << "whoa here we are" << std::endl;
					children_[selectedChild_]->HandleEvent(event);
				}
				child->Activate();
				return false; // Doesn't propagate events if the caller doesn't want to
			}
			else
				child->Deselect();
				
			n++;
		}
		selectedChild_ = -1;
	}
	return true;
}

bool Container::HasSelection() const
{
	return selectedChild_ >= 0;
}

void Container::SetVelocity(sf::Vector2f velocity) {
	velocity_ = velocity;
}

void Container::SetVelocity(float vx, float vy) {
	velocity_ = sf::Vector2f(vx, vy);
}

sf::Vector2f Container::GetVelocity() const {
	return velocity_;
}

/*
void Container::HandleEvent(const sf::Event& event)
{
    // If we have selected a child then give it events
	if (HasSelection() && children_[selectedChild_]->IsActive())
	{
		children_[selectedChild_]->HandleEvent(event);
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
		{
			SelectPrevious();
		}
		else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
		{
			SelectNext();
		}
		else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
		{
			if (HasSelection())
				children_[selectedChild_]->Activate();
		}
	}
}




void Container::Select(std::size_t index)
{
	if (children_[index]->IsSelectable())
	{
		if (HasSelection())
			children_[selectedChild_]->Deselect();

		children_[index]->Select();
		selectedChild_ = index;
	}
}
*/
}