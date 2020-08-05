#ifndef DATATABLES_HPP
#define DATATABLES_HPP

#include "resource_identifiers.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>

#include <vector>

class Enemy;

struct Direction
{
	Direction(float angle, float distance)
	: angle(angle)
	, distance(distance)
	{
	}

	float angle;
	float distance;
};

struct EnemyData
{
	int								hitpoints;
	float							speed;
	Textures::ID					texture;
	std::vector<Direction>			path;
};


//initializer
std::vector<EnemyData>	initializeEnemyData();

#endif // DATATABLES_HPP
