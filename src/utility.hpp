#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <sstream>

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

float toRadian(float degree)
{
    return 3.141592653589793238462643383f / 180.f * degree;
}

#include "utility.inl"
#endif // UTILITY_HPP