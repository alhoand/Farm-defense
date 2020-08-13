#pragma once

#include "resource_identifiers.hpp"
#include "enemies/enemy.hpp"
#include "towers/tower.hpp"
#include "towers/bullet.hpp"

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
	int				hitpoints;
	float			speed;
	Textures::ID	texture;
};

//initializer
std::vector<EnemyData>	InitializeEnemyData();
std::vector<Direction>	InitializeEnemyPath();

struct TowerData {
	Textures::ID	texture;
    float 			range;
    float 			reloadTime;
    int 			bulletType;
};

//initializer
std::vector<TowerData>	InitializeTowerData();

struct BulletData {
	Textures::ID	texture;
    float           speed;
    int             damage;
    int             damageDuration;
};

//initializer
std::vector<BulletData>	InitializeBulletData();

namespace GUIitems {
	enum ID {
            PauseButton,
			ResumeButton,
			TypeCount //this should be last
        };
}

struct GUIData {
	Textures::ID	texture;
    sf::IntRect     normalTexture;
    sf::IntRect     selectedTexture;
};

//initializer
std::vector<GUIData>	InitializeGUIData();


