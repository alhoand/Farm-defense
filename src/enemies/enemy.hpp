#ifndef ENEMY_HPP
#define ENEMY_HPP

//Initial header file for abstract enemy class
#include <vector>

#include "../bullet.hpp"
#include "../entity.hpp"
#include "../resource_identifiers.hpp"


/*  ***TODO***
* - all return values are void, to be changed for right ones
 - Intregrate the path to work with sfml vectors 
*/

class Enemy : public Entity {
    public:
        //Enemy types
        enum Type {
            Fire,
            Water,
            Leaf,
            TypeCount //enumerators are indexed so last one tells the count of previous ones 
        };
    public:
        //Constructors
        Enemy();
            
        Enemy(Type type, const TextureHolder &textures, int hp, int speed);

        //TODO: Integrate path with sfml 

        //virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

        void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

        // TODO: integrate path with sfml 
        /* virtual ~Enemy() {
            }
        } */

        //Take hit from a bullet
//        virtual void TakeHit(Bullet bullet);
        void TakeHit(Bullet bullet);
        unsigned int GetCategory() const;
        virtual sf::FloatRect getBoundingRect() const;

        //unsigned int GetCategory() const override;

    private:
        void updateMovementPattern(sf::Time dt);

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
        float travelledDistance_;
		std::size_t directionIndex_;
        int hitpoints_;
        int speed_;
};

#endif // ENEMY_HPP
