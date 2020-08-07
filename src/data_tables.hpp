#ifndef DATATABLES_HPP
#define DATATABLES_HPP

#include "resource_identifiers.hpp"
#include "bullet.hpp"

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
std::vector<EnemyData>	InitializeEnemyData();

struct TowerData {
    int range;
    float reloadTime;
    unsigned int bulletType;
};

//initializer
std::vector<TowerData>	InitializeTowerData();

struct BulletData {
    float           speed;
    int             damage;
    int             damageDuration;
};

//initializer
std::vector<BulletData>	InitializeBulletData();

#endif // DATATABLES_HPP
