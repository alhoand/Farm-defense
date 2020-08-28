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
        Application app;
        app.Run();
    } catch (std::exception& e) {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    }


    return 0;
}