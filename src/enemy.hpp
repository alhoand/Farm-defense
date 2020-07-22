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

        //Update the state of enemy, should return something!
        /* Possible cases:
        * 1. enemy is alive (hp > 0) 
        *   - and not at the end of the path
        *   => move enemy forward (change position) 
        *   - and it is at the end of the path)
            => game lost
        * 2. enemy is dead (hp <= 0)
        *  => return something to indicate enemy should be deleted from the game field
        * TODO:
        * Long lasting damage implementation
        */
        void Update() {
            if (hitpoints_ > 0) {
                //move enemy or game lost
            } else {
                //indicate game field somehow that enemy is dead
            }
        }

        //Take hit from a bullet
        virtual void TakeHit(Bullet bullet) = 0;

    protected:
        int hitpoints_;
        int speed_;
        std::vector<Position*> path_;
        Position* position_;
};