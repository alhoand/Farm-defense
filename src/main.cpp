#include<iostream>
#include<vector>

#include "game_field.hpp"
#include "tower.hpp"
#include "enemy.hpp"
#include "bullet.hpp"
#include "position.hpp"
#include "towers/test_tower.hpp"
#include "enemies/test_enemy.hpp"
#include <SFML/Graphics.hpp>
 
int main(){
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
    TestEnemy* enemy1 = new TestEnemy(path1);

    
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}


/*

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}*/