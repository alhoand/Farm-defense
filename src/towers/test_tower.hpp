#pragma once

#include "../tower.hpp"

#include <iostream>
#include <string>

class TestTower: public Tower {
	public:
		TestTower(Position p): Tower() { }

		virtual ~TestTower() { }
		
		void Update(){
				std::cout << "TestTower updated" << std::endl;
		}
		
		void Shoot(){
				std::cout << "TestTower shot" << std::endl;
		}
};