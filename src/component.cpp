#include "component.hpp"

namespace GUI
{

Component::Component()
: isSelected_(false)
, isActive_(false)
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

}