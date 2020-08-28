#include "label.hpp"
#include "utility.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

Label::Label(const std::string& text, const FontHolder& fonts)
: text_(text, fonts.Get(Fonts::Main), 16)
{
}

Label::Label(const std::string& text, const FontHolder& fonts, unsigned int fontSize, Fonts::ID fontType)
: text_(text, fonts.Get(fontType), fontSize)
{

}
void Label::CenterTextOrigin() {
	CenterOrigin(text_);
}

bool Label::IsSelectable() const
{
    return false;
}

sf::FloatRect Label::GetGlobalBounds() const{
	return GetWorldTransform().transformRect(text_.getGlobalBounds());
}

bool Label::HandleEvent(const sf::Event&)
{
	return true; // Propagate events through
}

void Label::Draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(text_, states);
	//DrawBoundingRect(target, states);
}
// Sets text of the label element
// By default centers the text, otherwise set second param false
void Label::SetText(const std::string& text, bool center)
{
	text_.setString(text);
	if (center)
		CenterOrigin(text_);
}

void Label::SetColor(const sf::Color color, bool outline)
{
	text_.setFillColor(color);
	if (outline)
	{
		text_.setOutlineColor(sf::Color(186,15,0));	
		text_.setOutlineThickness(0.75);
	}
}

}