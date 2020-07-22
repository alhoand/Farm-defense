#pragma once

#include "position.hpp"

/*  ***TODO***
* - all return values are void, to be changed for right ones
*/

//Example of different bullet types, used if bullet is not an abstract class.
enum BulletType {
    Ice,
    Fire,
    Wood,
};

//First implementation of Bullet class
class Bullet {
    public:
        //Constructor
        Bullet(BulletType type, Position position, int damage, int damage_duration) 
            : type_(type), position_(position), damage_(damage), damage_duration_(damage_duration) {} 

        //Destructor, only needed if abstract class
        //virtual ~Bullet() {};

        //Update the state of the bullet, should be virtual if class is abstract
        void Update();

        //could also return damage duration, depends on how the hit to enemy is implemented
        int GetDamage() {
            return damage_;
        };

        //More getter functions, and some way to destroy bullet when it hits an enemy

    protected:
        BulletType type_;
        Position position_;
        int damage_;
        int damage_duration_;
};