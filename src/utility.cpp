#include "utility.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <cmath>
#include <random>
#include <ctime>

namespace
{
	std::default_random_engine createRandomEngine()
	{
		auto seed = static_cast<unsigned long>(std::time(nullptr));
		return std::default_random_engine(seed);
	}

	auto RandomEngine = createRandomEngine();
}

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

int RandomInt(int exclusiveMax)
{
	std::uniform_int_distribution<> distr(0, exclusiveMax - 1);
	return distr(RandomEngine);
}