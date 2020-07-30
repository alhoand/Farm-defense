#pragma once

//Initial header file for abstract enemy class
#include <vector>

#include "position.hpp"
#include "bullet.hpp"
#include "entity.hpp"
#include "resource_identifiers.hpp"
/*  ***TODO***
* - all return values are void, to be changed for right ones
 - Intregrate the path to work with sfml vectors 
*/

class Enemy : public Entity {
    public:
        enum class Type {
            Fire,
            Water,
            Leaf
        };
        //Constructors
        Enemy();
            
        Enemy(Type type, const TextureHolder &textures, int hp, int speed);

        //TODO: Integrate path with sfml 

       /* Enemy(int hp, int speed, std::vector<Position*> path)
            : hitpoints_(hp), speed_(speed), path_(path) 
            {
                position_ = path_[0];
            } 
        */

        virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;


        // TODO: integrate path with sfml 
        virtual ~Enemy() {
        /*    for (auto it = path_.begin(); it != path_.end(); it++) {
                delete *it;
            }*/
        }

        //Take hit from a bullet
        virtual void TakeHit(Bullet bullet);

        unsigned int GetCategory() const override;

    protected:

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
        virtual void UpdateCurrent(sf::Time dt) override;

        Textures::ID ToTextureID(Enemy::Type type);

        Type type_;
        sf::Sprite sprite_;
        int hitpoints_;
        int speed_;
        std::vector<Position*> path_;
        Position* position_;
};