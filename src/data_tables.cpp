#include "data_tables.hpp"


//hardcoded path which is same fo all enemies
//TODO add rest of the enemies
std::vector<EnemyData> InitializeEnemyData()
{
    //DEBUG
    std::cout << "DEBUG: Initializing enemy data" << std::endl; 

	std::vector<EnemyData> data(Enemy::TypeCount);

	data[Enemy::Fire].hitpoints = 50;
	data[Enemy::Fire].speed = 50.f;
	data[Enemy::Fire].texture = Textures::Fire;

	data[Enemy::Leaf].hitpoints = 10;
	data[Enemy::Leaf].speed = 50.f;
	data[Enemy::Leaf].texture = Textures::Leaf;

	return data;
}

std::vector<Direction> InitializeEnemyPath() 
{
	std::vector<Direction> path;
	
	path.push_back(Direction(0.f, 400.f));
	path.push_back(Direction(+90.f, 250.f));
	path.push_back(Direction(0.f, 450.f));
	path.push_back(Direction(-90.f, 200.f));

	return path;
}

std::vector<TowerData> InitializeTowerData() {
	std::vector<TowerData> data(Tower::TypeCount);

	data[Tower::Fire].texture = Textures::FireTower;
	data[Tower::Fire].range = 400;
    data[Tower::Fire].reloadTime = 5;
    data[Tower::Fire].bulletType = Bullet::FireBullet;

	data[Tower::Water].texture = Textures::WaterTower;
	data[Tower::Water].range = 100;
    data[Tower::Water].reloadTime = 0.5;
    data[Tower::Water].bulletType = Bullet::IceBullet;

	data[Tower::Leaf].texture = Textures::LeafTower;
	data[Tower::Leaf].range = 50;
    data[Tower::Leaf].reloadTime = 0.5;
    data[Tower::Leaf].bulletType = Bullet::WoodBullet;

	return data;
}

std::vector<BulletData>	InitializeBulletData() {
	std::vector<BulletData> data(Bullet::TypeCount);

	data[Bullet::FireBullet].texture = Textures::FireBullet;
	data[Bullet::FireBullet].speed = 100.f;
	data[Bullet::FireBullet].damage = 10;
	data[Bullet::FireBullet].damageDuration = 1;

	data[Bullet::IceBullet].texture = Textures::IceBullet;
	data[Bullet::IceBullet].speed = 150.f;
	data[Bullet::IceBullet].damage = 1;
	data[Bullet::IceBullet].damageDuration = 1;

	data[Bullet::IceBullet].texture = Textures::IceBullet;
	data[Bullet::WoodBullet].speed = 75.f;
	data[Bullet::WoodBullet].damage = 1;
	data[Bullet::WoodBullet].damageDuration = 5;

	return data;
}