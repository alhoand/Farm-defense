#include "button.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <cmath>

namespace GUI
{

Button::Button(const FontHolder& fonts, const TextureHolder& textures)
: callback_()
, normalTexture_(textures.Get(Textures::ID::ButtonNormal))
, selectedTexture_(textures.Get(Textures::ID::ButtonSelected))
, pressedTexture_(textures.Get(Textures::ID::ButtonPressed))
, sprite_()
, text_("", fonts.Get(Fonts::ID::Main), 16)
, isToggle_(false)
{
	sprite_.setTexture(normalTexture_);

	sf::FloatRect bounds = sprite_.getLocalBounds();
	text_.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

void Button::SetCallback(Callback callback)
{
	callback_ = std::move(callback);
}

void Button::SetText(const std::string& text)
{
	text_.setString(text);
	sf::FloatRect bounds = text_.getLocalBounds();
	text_.setOrigin(::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void Button::SetToggle(bool flag)
{
	isToggle_ = flag;
}

sf::FloatRect Button::GetGlobalBounds(){
	return sprite_.getGlobalBounds();
}

bool Button::IsSelectable() const
{
    return true;
}

void Button::Select()
{
	Component::Select();

	sprite_.setTexture(selectedTexture_);
}

void Button::Deselect()
{
	Component::Deselect();

	sprite_.setTexture(normalTexture_);
}

void Button::Activate()
{
	Component::Activate();

    // If we are toggle then we should show that the button is pressed and thus "toggled".
	if (isToggle_)
		sprite_.setTexture(pressedTexture_);

	if (callback_)
		callback_();

    // If we are not a toggle then deactivate the button since we are just momentarily activated.
	if (!isToggle_)
		Deactivate();
}

void Button::Deactivate()
{
	Component::Deactivate();

	if (isToggle_)
	{
        // Reset texture to right one depending on if we are selected or not.
		if (IsSelected())
			sprite_.setTexture(selectedTexture_);
		else
			sprite_.setTexture(normalTexture_);
	}
}

void Button::HandleEvent(const sf::Event&)
{
}

void Button::Draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite_, states);
	target.draw(text_, states);
}

}