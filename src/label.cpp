#include "label.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

Label::Label(const std::string& text, const FontHolder& fonts)
: text_(text, fonts.Get(Fonts::Main), 16)
{
}

bool Label::IsSelectable() const
{
    return false;
}

void Label::HandleEvent(const sf::Event&)
{
}

void Label::Draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(text_, states);
}

void Label::SetText(const std::string& text)
{
	text_.setString(text);
}

}