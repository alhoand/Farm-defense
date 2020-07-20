#pragma once

#include <vector>
#include <iostream>

#include "../enemy.hpp"
#include "../position.hpp"
#include "../bullet.hpp"

class TestEnemy : public Enemy {
    public:
        //Constructor
        TestEnemy(std::vector<Position*> path) 
            : Enemy(10, 1, path) 
            {
                std::cout << "New enemy created!" << std::endl;
            }

        //Destructor, implement when class is abstract
        //~TestEnemy() = default;

        //Update the state of enemy
        virtual void Update() {
            std::cout << "Enemy updated" << std::endl;
            //position_ = path_[6]; 
        }

        //Take damage
        virtual void TakeDamage(Bullet bullet) {
            std::cout << "Enemy takes damage" << std::endl;
            hitpoints_ -= 1;
        }


};