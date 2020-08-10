#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <sstream>
#include <cassert>
#include <cmath>

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

#include "utility.inl"
#endif // UTILITY_HPP