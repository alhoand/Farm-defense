#ifndef DATATABLES_HPP
#define DATATABLES_HPP

#include "resource_identifiers.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>

#include <vector>


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

//hitpoints and speed are in datatable and enemy class, check if this is necessary
struct EnemyData
{
	int								hitpoints;
	float							speed;
	Textures::ID					texture;
	std::vector<Direction>			path;
};

//initializer
std::vector<EnemyData>	initializeEnemyData();

struct TowerData {
    int range;
    // float direction - this changes, maybe not needed here
    float reload_speed;
    Bullet bullet;
	// float speed - this could be default for all types
};

//initializer
std::vector<TowerData>	initializeTowerData();

#endif // DATATABLES_HPP
