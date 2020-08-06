#pragma once

//Initial header file for abstract tower class
#include "scene_node.hpp"
#include "bullet.hpp"
#include "category.hpp"
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
        
        // The constructor for now. Most of the parameters should be given automatically, 
        // depending on type (inherited class)
        Tower(Type type, const TextureHolder &textures, int range, int reload_speed, Bullet bullet);

        //Destructor
        virtual ~Tower() { };

        virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

        //Update the state of the tower, should be virtual
        virtual void Update() { }

        //Shoot an enemy, should be virtual
        virtual void Shoot() { }

        virtual unsigned int GetCategory() const override;

        // This sets the permission for the tower to move
        // for now: this maybe is a clumsy way to achieve this
        void SetMovePermission(bool permissionToMove);

        // Getter of permission to move
        bool CanMove() const;

        // Sets the tower moving with state=true, stops with state=false.
        // Returns true if setting was succesful
        bool SetMoveState(bool state);

        // Getter that tells if the tower is being moved by the player
        bool IsMoving() const;

        virtual sf::FloatRect GetBoundingRect() const;

        static Textures::ID ToTextureID(Type type);


    protected:
        // Helper that makes textures::ID-types from Tower::Types
        Tower::Type type_;
        int range_;
        sf::Sprite sprite_;
        //Position position_;
        //enemies_in_range_;
        int reload_speed_;
        Bullet bullet_;
};