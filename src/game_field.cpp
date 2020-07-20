
#include "game_field.hpp"


GameField::GameField(){}

void GameField::AddTower(Tower* t){
	towers_.push_back(t);
}

void GameField::Update(){
	std::cout << "updating game field" << std::endl;
}