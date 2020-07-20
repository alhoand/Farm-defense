#pragma once

//Initial header file for abstract tower class
#include <list>

#include "enemy.hpp"
#include "tower.hpp"
#include "bullet.hpp"

/*  ***TODO***
* - all return values are void, to be changed for right ones
*/

class GameField {
    public:
        //Constructor
        GameField();

        //Destructor
        //virtual ~GameField();

        //Update whole game field, should be virtual
        void Update();

    private:
        std::list<Tower> towers_;
        std::list<Enemy> enemies_;
        std::list<Bullet> bullets_;
};