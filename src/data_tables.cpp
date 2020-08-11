#include "data_tables.hpp"
#include "enemies/enemy.hpp"
#include "tower.hpp"
#include "bullet.hpp"

//hardcoded path for enemies

std::vector<EnemyData> InitializeEnemyData()
{
    //DEBUG
    std::cout << "DEBUG: Initializing enemy data" << std::endl; 

	std::vector<EnemyData> data(Enemy::TypeCount);


	data[Enemy::Fire].hitpoints = 50;
	data[Enemy::Fire].speed = 50.f;
	data[Enemy::Fire].texture = Textures::Fire;
	data[Enemy::Fire].path.push_back(Direction(0.f, 400.f));
	data[Enemy::Fire].path.push_back(Direction(+90.f, 500.f));
	data[Enemy::Fire].path.push_back(Direction(0.f, 450.f));
    data[Enemy::Fire].path.push_back(Direction(-90.f, 200.f));

    data[Enemy::Leaf].hitpoints = 50;
	data[Enemy::Leaf].speed = 50.f;
	data[Enemy::Leaf].texture = Textures::Fire;
	data[Enemy::Leaf].path.push_back(Direction(0.f, 400.f));
	data[Enemy::Leaf].path.push_back(Direction(+90.f, 500.f));
	data[Enemy::Leaf].path.push_back(Direction(0.f, 450.f));
    data[Enemy::Leaf].path.push_back(Direction(-90.f, 200.f));


    // TODO
    //   add rest of the enemy types
    

	return data;
}

std::vector<TowerData> InitializeTowerData() {
	std::vector<TowerData> data(Tower::TypeCount);

	data[Tower::Fire].range = 75;
    data[Tower::Fire].reloadTime = 1;
    data[Tower::Fire].bulletType = Bullet::FireBullet;

	data[Tower::Water].range = 50;
    data[Tower::Water].reloadTime = 0.5;
    data[Tower::Water].bulletType = Bullet::IceBullet;

	data[Tower::Leaf].range = 30;
    data[Tower::Leaf].reloadTime = 0.5;
    data[Tower::Leaf].bulletType = Bullet::WoodBullet;

	return data;
}

std::vector<BulletData>	InitializeBulletData() {
	std::vector<BulletData> data(Bullet::TypeCount);

	data[Bullet::FireBullet].speed = 100.f;
	data[Bullet::FireBullet].damage = 10;
	data[Bullet::FireBullet].damageDuration = 1;

	data[Bullet::IceBullet].speed = 150.f;
	data[Bullet::IceBullet].damage = 1;
	data[Bullet::IceBullet].damageDuration = 1;

	data[Bullet::WoodBullet].speed = 75.f;
	data[Bullet::WoodBullet].damage = 1;
	data[Bullet::WoodBullet].damageDuration = 5;

	return data;
}