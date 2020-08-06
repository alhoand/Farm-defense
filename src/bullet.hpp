#pragma once

#include "entity.hpp"
#include "resource_identifiers.hpp"

/*  ***TODO***
* - all return values are void, to be changed for right ones
*/

//Example of different bullet types, used if bullet is not an abstract class.


//First implementation of Bullet class
class Bullet : public Entity {
    public:
        enum Type 
        {
            Ice,
            FireBullet,
            Wood,
            TypeCount
        };

    public:
        //Constructor for now
        Bullet(Type type, int damage, int damage_duration, const TextureHolder& textures);

        //Destructor, only needed if abstract class
        //virtual ~Bullet() {};

        //could also return damage duration, depends on how the hit to enemy is implemented
        int GetDamage() const;

        virtual sf::FloatRect GetBoundingRect() const;

        //More getter functions, and some way to destroy bullet when it hits an enemy
    private:
        virtual void UpdateCurrent(sf::Time dt);
        virtual void DrawCurrent(sf::RenderTarget& target,sf::RenderStates states) const;
        Textures::ID ToTextureID(Bullet::Type type);
    protected:
        Type type_;
        sf::Sprite sprite_;
        sf::Vector2f targetDirection_;
        int damage_;
        int damage_duration_;
};