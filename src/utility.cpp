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

float ToRadian(float degree)
{
    return 3.141592653589793238462643383f / 180.f * degree;
}

float Length(sf::Vector2f vector)
{
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f UnitVector(sf::Vector2f vector)
{
	assert(vector != sf::Vector2f(0.f, 0.f));
	return vector / Length(vector);
}