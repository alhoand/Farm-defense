#include<iostream>
#include<vector>
#include <SFML/Graphics.hpp>
#include "game_field.hpp"
#include "game.hpp"
#include "tower.hpp"
#include "enemy.hpp"
#include "bullet.hpp"
#include "position.hpp"
#include "towers/test_tower.hpp"
#include "enemies/test_enemy.hpp"

#include <exception>
 
int main(){
    try {


        Position pos = Position(1,2);   
        std::cout << pos << std::endl;
    
        TestTower testi = TestTower(Position(1,2));
        
        std::cout << "Testing tower" << std::endl;
        testi.Shoot();
        testi.Update();
        std::cout << "Testing done" << std::endl;
    
        std::cout << "Testing Enemy" << std::endl;
        std::vector<Position*> path1;
        Position* p1 = new Position(1,1);
        path1.push_back(p1);
        std::cout << *p1 << std::endl;
       //  TestEnemy* enemy1 = new TestEnemy(path1);
        Game game;
        game.Run();
    } catch (std::exception& e) {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    }


    return 0;
}