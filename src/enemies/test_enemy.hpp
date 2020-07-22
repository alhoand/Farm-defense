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
        /* Possible cases:
        * 1. enemy is alive (hp > 0) and not at the end of the path
        *   => move enemy forward (change position) 
        * 2. enemy is at the end of the path
        *   => game lost
        * 3. enemy is dead (hp <= 0)
        *  => ??? tell gamefield or do nothing?
        */
        virtual void Update() {
            std::cout << "Enemy updated" << std::endl;
        }

        //Take damage
        /* Damage depends on bullet, certain bullets can have stronger or weaker effects on certain enemies.
        * 1. check if bullet is certain type 
        *   => if true take damage more or less than normally
        * 2. otherwise take damage or slow down for number of ticks
        */
        virtual void TakeHit(Bullet bullet) {
            std::cout << "Enemy takes damage" << std::endl;
            hitpoints_ -= 1;
        }


};