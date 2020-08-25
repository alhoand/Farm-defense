#include<iostream>
#include<vector>
#include <SFML/Graphics.hpp>
#include "application.hpp"
#include "game_field.hpp"
#include "towers/tower.hpp"
#include "enemies/enemy.hpp"
#include "towers/bullet.hpp"

#include <exception>
 
int main(){
    try {


        //Position pos = Position(1,2);   
        //std::cout << pos << std::endl;
    
        //TestTower testi(Position(1,2));
        /*
        std::cout << "Testing tower" << std::endl;
        testi.Shoot();
        testi.Update();
        std::cout << "Testing done" << std::endl;
    
        std::cout << "Testing Enemy" << std::endl;
        std::vector<Position*> path1;
        Position* p1 = new Position(1,1);
        path1.push_back(p1);
        std::cout << *p1 << std::endl;*/
       //  TestEnemy* enemy1 = new TestEnemy(path1);
        Application app;
        app.Run();
    } catch (std::exception& e) {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    }


    return 0;
}