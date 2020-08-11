#include "utility.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <cmath>


void CenterOrigin(sf::Sprite sprite) {
    sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(::floor(bounds.left + bounds.width / 2.f), ::floor(bounds.top + bounds.height / 2.f));
}

void CenterOrigin(sf::Text& text) {
    sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(::floor(bounds.left + bounds.width / 2.f), ::floor(bounds.top + bounds.height / 2.f));
}