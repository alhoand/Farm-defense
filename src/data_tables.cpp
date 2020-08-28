#include "data_tables.hpp"


//hardcoded path which is same fo all enemies
//TODO add rest of the enemies
std::vector<EnemyData> InitializeEnemyData()
{
    //DEBUG
    std::cout << "DEBUG: Initializing enemy data" << std::endl; 

	std::vector<EnemyData> data(Enemy::TypeCount);

	// basic enemy resists slowing down and slowns down less than other enemies5
	data[Enemy::Basic].hitpoints = 10;
	data[Enemy::Basic].speed = 50.f;
	data[Enemy::Basic].slowDownRate = 0.2;
	data[Enemy::Basic].texture = Textures::Fire;
	data[Enemy::Basic].worthOfMoney = 5;

	data[Enemy::Multiplying].hitpoints = 10;
	data[Enemy::Multiplying].speed = 50.f;
	data[Enemy::Multiplying].slowDownRate = 0.5;
	data[Enemy::Multiplying].texture = Textures::Leaf;
	data[Enemy::Multiplying].worthOfMoney = 10;
	
	// Bulk enemy slows down more than other enemies
	data[Enemy::Bulk].hitpoints = 50;
	data[Enemy::Bulk].speed = 50.f;
	data[Enemy::Bulk].slowDownRate = 0.7;
	data[Enemy::Bulk].texture = Textures::Water;
	data[Enemy::Bulk].worthOfMoney = 15;

	data[Enemy::Fast].hitpoints = 20;
	data[Enemy::Fast].speed = 100.f;
	data[Enemy::Fast].slowDownRate = 0.5;
	data[Enemy::Fast].texture = Textures::Water;
	data[Enemy::Fast].worthOfMoney = 20;


	return data;
}

std::vector<Direction> InitializeEnemyPath() 
{
	std::vector<Direction> path;
	
	path.push_back(Direction(0.f, 200.f));
	path.push_back(Direction(+90.f, 400.f));
	path.push_back(Direction(0.f, 200.f));
	path.push_back(Direction(-90.f, 550.f));
	path.push_back(Direction(0.f, 250.f));
	path.push_back(Direction(+90.f, 400.f));
	path.push_back(Direction(0.f, 200.f));
	path.push_back(Direction(-90.f, 1500.f));

	return path;
}

std::vector<TowerData> InitializeTowerData()
{
	std::vector<TowerData> data(Tower::TypeCount);

	float capExCoefficient = 0.9f; // how many percent of the original price you get after selling the tower

	data[Tower::Type::Basic].texture = Textures::ID::BasicTower;
	data[Tower::Type::Basic].range = 200;
	data[Tower::Type::Basic].reloadTime = 2;
	data[Tower::Type::Basic].price = 150;
	data[Tower::Type::Basic].sellPrice = data[Tower::Type::Basic].price * capExCoefficient;
	data[Tower::Type::Basic].name = "Basic Tower";

	data[Tower::Type::Super].texture = Textures::ID::SuperTower;
	data[Tower::Type::Super].range = 250;
	data[Tower::Type::Super].reloadTime = 0.5;
	data[Tower::Type::Super].scale = 0.5;
	data[Tower::Type::Super].price = 600;
	data[Tower::Type::Super].sellPrice = data[Tower::Type::Super].price * capExCoefficient;
	data[Tower::Type::Super].name = "Super Tower";

	data[Tower::Type::Slowing].texture = Textures::ID::SlowingTower;
	data[Tower::Type::Slowing].range = 200;
	data[Tower::Type::Slowing].reloadTime = 0;
	data[Tower::Type::Slowing].price = 200;
	data[Tower::Type::Slowing].sellPrice = data[Tower::Type::Slowing].price * capExCoefficient;
	data[Tower::Type::Slowing].name = "Slowing Tower";

	data[Tower::Type::Bombing].texture = Textures::ID::BombingTower;
	data[Tower::Type::Bombing].range = 150;
	data[Tower::Type::Bombing].reloadTime = 3;
	data[Tower::Type::Bombing].price = 350;
	data[Tower::Type::Bombing].sellPrice = data[Tower::Type::Bombing].price * capExCoefficient;
	data[Tower::Type::Bombing].name = "Bomb Tower";

	return data;
}

//initializer
std::vector<BulletData>	InitializeBulletData() {
	std::vector<BulletData> data(Bullet::TypeCount);

	data[Bullet::Type::Basic].texture = Textures::ID::BasicBullet;
	data[Bullet::Type::Basic].speed = 150;
	data[Bullet::Type::Basic].damage = 10;

	data[Bullet::Type::Super].texture = Textures::ID::SuperBullet;
	data[Bullet::Type::Super].speed = 200;
	data[Bullet::Type::Super].damage = 5;

	data[Bullet::Type::Bomb].texture = Textures::ID::Bomb;
	data[Bullet::Type::Bomb].speed = 150;
	data[Bullet::Type::Bomb].damage = 10;

	return data;
}

std::vector<GUIData>	InitializeGUIData() {
	std::vector<GUIData> data(GUIitems::ID::TypeCount);

	data[GUIitems::ID::PauseButton].texture = Textures::Buttons;
	data[GUIitems::ID::PauseButton].normalTexture = sf::IntRect(108,0,55,53);
	data[GUIitems::ID::PauseButton].selectedTexture = sf::IntRect(0,0,54,53);

	data[GUIitems::ID::ResumeButton].texture = Textures::Buttons;
	data[GUIitems::ID::ResumeButton].normalTexture = sf::IntRect(0,53,55,53);
	data[GUIitems::ID::ResumeButton].selectedTexture = sf::IntRect(54,0,55,53);
	return data;
}
