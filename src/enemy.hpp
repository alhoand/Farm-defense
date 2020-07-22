#pragma once

//Initial header file for abstract enemy class
#include <vector>

#include "position.hpp"
#include "bullet.hpp"

/*  ***TODO***
* - all return values are void, to be changed for right ones
*/

class Enemy {
    public:
        //Constructor
        Enemy(int hp, int speed, std::vector<Position*> path)
            : hitpoints_(hp), speed_(speed), path_(path) 
            {
                position_ = path_[0];
            }

        //Destructor
        virtual ~Enemy() {
            for (auto it = path_.begin(); it != path_.end(); it++) {
                delete *it;
            }
        }

        //Update the state of enemy
        virtual void Update() = 0;

        //Take hit from a bullet
        virtual void TakeHit(Bullet bullet) = 0;

    protected:
        int hitpoints_;
        int speed_;
        std::vector<Position*> path_;
        Position* position_;
};