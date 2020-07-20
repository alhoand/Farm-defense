#include<iostream>

#include "game_field.hpp"
#include "tower.hpp"
#include "enemy.hpp"
#include "bullet.hpp"
#include "test_tower.hpp"
#include "position.hpp"
 
int main(){
	Position pos = Position(1,2);   
    std::cout << pos << std::endl;
   
	TestTower testi = TestTower(Position(1,2));
	
	std::cout << "Testing tower" << std::endl;
	testi.Shoot();
	testi.Update();
	std::cout << "Testing done" << std::endl;
}