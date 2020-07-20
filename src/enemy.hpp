#pragma once

//Initial header file for abstract enemy class

#include "position.hpp"

/*  ***TODO***
* - all return values are void, to be changed for right ones
*/

class Enemy {
    public:
        //Constructor
        Enemy();

        //Destructor, implement when class is abstract
        //virtual ~Enemy();

        //Update the state of enemy, should be virtual
        void Update();

        //Take damage, should be virtual
        void TakeDamage();

    protected:
        int hitpoints_;
        Position position_;
        int speed_;

};