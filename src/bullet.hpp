#pragma once

#include "position.hpp"

/*  ***TODO***
* - all return values are void, to be changed for right ones
*/

class Bullet {
    public:
        //Constructor
        Bullet();

        //Destructor
        virtual ~Bullet() {};

        //Update the state of the bullet, should be virtual
        void Update();

    protected:
        Position position_;
        int damage_;
        int damage_duration_;
};