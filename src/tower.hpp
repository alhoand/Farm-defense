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
        Tower(Position p) : position_(p) {};

        //Destructor
        virtual ~Tower() {};

        //Update the state of the tower, should be virtual
        virtual void Update() = 0;

        //Shoot an enemy, should be virtual
        virtual void Shoot() = 0;

    protected:
        int range_;
        Position position_;
        //enemies_in_range_;
        int reload_speed_;
        //Bullet bullet_type_;
};