#include "data_tables.hpp"


//hardcoded path which is same fo all enemies
//TODO add rest of the enemies
std::vector<EnemyData> InitializeEnemyData()
{
    //DEBUG
    std::cout << "DEBUG: Initializing enemy data" << std::endl; 

	std::vector<EnemyData> data(Enemy::TypeCount);

	data[Enemy::Basic].hitpoints = 10;
	data[Enemy::Basic].speed = 50.f;
	data[Enemy::Basic].slowDownRate = 0.8;
	data[Enemy::Basic].texture = Textures::Fire;
	data[Enemy::Basic].scorepoints = 50;

	data[Enemy::Multiplying].hitpoints = 10;
	data[Enemy::Multiplying].speed = 50.f;
	data[Enemy::Multiplying].slowDownRate = 0.5;
	data[Enemy::Multiplying].texture = Textures::Leaf;
	data[Enemy::Multiplying].scorepoints = 10;
	

	data[Enemy::Bulk].hitpoints = 50;
	data[Enemy::Bulk].speed = 50.f;
	data[Enemy::Bulk].slowDownRate = 0.5;
	data[Enemy::Bulk].texture = Textures::Water;
	data[Enemy::Bulk].scorepoints = 500;

	data[Enemy::Fast].hitpoints = 20;
	data[Enemy::Fast].speed = 100.f;
	data[Enemy::Fast].slowDownRate = 0.5;
	data[Enemy::Fast].texture = Textures::Water;
	data[Enemy::Fast].scorepoints = 100;


	return data;
}

std::vector<Direction> InitializeEnemyPath() 
{
	std::vector<Direction> path;
	
	path.push_back(Direction(0.f, 400.f));
	path.push_back(Direction(+90.f, 550.f));
	path.push_back(Direction(0.f, 500.f));
	path.push_back(Direction(-90.f, 650.f));
	path.push_back(Direction(0.f, 330.f));
	path.push_back(Direction(+90.f, 1200.f));

	return path;
}

std::vector<TowerData> InitializeTowerData()
{
	std::vector<TowerData> data(Enemy::TypeCount);

	data[Tower::Type::Super].scale = 0.5;

	return data;
}

std::vector<GUIData>	InitializeGUIData() {
	std::vector<GUIData> data(GUIitems::ID::TypeCount);

	data[GUIitems::ID::PauseButton].texture = Textures::Buttons;
	data[GUIitems::ID::PauseButton].normalTexture = sf::IntRect(108,0,55,53);
	data[GUIitems::ID::PauseButton].selectedTexture = sf::IntRect(0,0,54,53);

	data[GUIitems::ID::ResumeButton].texture = Textures::Buttons;
	data[GUIitems::ID::ResumeButton].normalTexture = sf::IntRect(54,0,55,53);
	data[GUIitems::ID::ResumeButton].selectedTexture = sf::IntRect(163,0,55,54);
	return data;
}
