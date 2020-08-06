#include "data_tables.hpp"
#include "enemies/enemy.hpp"
#include "tower.hpp"

//hardcoded path for enemies
/*
std::vector<EnemyData> initializeEnemyData()
{
    //DEBUG
    std::cout << "DEBUG: Initializing enemy data" << std::endl; 

	std::vector<EnemyData> data(Enemy::TypeCount);

	data[Enemy::Fire].hitpoints = 50;
	data[Enemy::Fire].speed = 50.f;
	data[Enemy::Fire].texture = Textures::Fire;
	data[Enemy::Fire].path.push_back(Direction(0.f, 400.f));
	data[Enemy::Fire].path.push_back(Direction(+90.f, 200.f));
	data[Enemy::Fire].path.push_back(Direction(0.f, 400.f));
    data[Enemy::Fire].path.push_back(Direction(-90.f, 200.f));

    data[Enemy::Leaf].hitpoints = 50;
	data[Enemy::Leaf].speed = 50.f;
	data[Enemy::Leaf].texture = Textures::Fire;
	data[Enemy::Leaf].path.push_back(Direction(0.f, 400.f));
	data[Enemy::Leaf].path.push_back(Direction(+90.f, 200.f));
	data[Enemy::Leaf].path.push_back(Direction(0.f, 400.f));
    data[Enemy::Leaf].path.push_back(Direction(-90.f, 200.f));


    // TODO
    //   add rest of the enemy types
    

	return data;
}*/

/*
std::vector<TowerData> initializeTowerData() {
	std::vector<TowerData> data(Tower::TypeCount);

	data[Tower::Fire].range = 50;
    data[Tower::Fire].reload_speed = 0.5;
    data[Tower::Fire].bullet = Bullet::Fire;

    // TODO
    //   add rest of the enemy types
    

	return data;
}
*/