#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <sstream>
#include <cassert>
#include <cmath>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>

namespace sf {
	class Sprite;
	class Text;
}

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
std::string toString(const T& value);

void CenterOrigin(sf::Sprite& sprite);
void CenterOrigin(sf::Text& text);

float ToRadian(float degree);

float Length(sf::Vector2f vector);

sf::Vector2f UnitVector(sf::Vector2f vector);

#include "utility.inl"
#endif // UTILITY_HPP