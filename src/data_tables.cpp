#include <data_tables.hpp>
#include <enemy.hpp>

//hardcoded path for enemies
std::vector<EnemyData> initializeEnemyData()
{
	std::vector<EnemyData> data(Enemy::TypeCount);

	data[Enemy::Fire].hitpoints = 100;
	data[Enemy::Fire].speed = 100.f;
	data[Enemy::Fire].texture = Textures::Fire;
	data[Enemy::Fire].path.push_back(Direction(+90.f, 80.f));
	data[Enemy::Fire].path.push_back(Direction(0.f, 160.f));
	data[Enemy::Fire].path.push_back(Direction(+90.f, 80.f));

    /*TODO
    * add rest of the enemy types
    */

	return data;
}


