#pragma once

//Initial header file for abstract tower class
#include "position.hpp"
#include "bullet.hpp"
#include "entity.hpp"
#include "resource_identifiers.hpp"

/*  ***TODO***
* - all return values are void, to be changed for right ones
*/

class Tower : public Entity {
    public:
        enum class Type {
            Fire,
            Water,
            Leaf
        };

        //Constructors

        // Default constructor - is it needed?
        Tower();

        // Constructor which is given the position
        // Tower(Position p);
        
        // The constructor for now. Most of the parameters should be given automatically
        Tower(Type type, const TextureHolder &textures, Position position, int range, int reload_speed, Bullet bullet);

        //Destructor
        virtual ~Tower();

        virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

        //Update the state of the tower, should be virtual
        virtual void Update() = 0;

        //Shoot an enemy, should be virtual
        virtual void Shoot() = 0;

    protected:
        virtual void UpdateCurrent(sf::Time dt);

        Type type_;
        sf::Sprite sprite_;
        int range_;
        Position position_;
        //enemies_in_range_;
        int reload_speed_;
        Bullet bullet_;
};