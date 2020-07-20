#pragma once

//Initial header file for abstract tower class
#include "position.hpp"
#include "bullet.hpp"

/*  ***TODO***
* - all return values are void, to be changed for right ones
*/

class Tower {
    public:
        //Constructor
        Tower();

        //Destructor
        //virtual ~Tower();

        //Update the state of the tower, should be virtual
        void Update();

        //Shoot an enemy, should be virtual
        void Shoot();

    protected:
        int range_;
        Position position_;
        //enemies_in_range_;
        int reload_speed_;
        Bullet bullet_type_;
};