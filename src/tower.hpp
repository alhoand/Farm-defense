#pragma once

//Initial header file for abstract tower class
#include "scene_node.hpp"
#include "position.hpp"
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
        //Constructor
        Tower();


        
        Tower(Type type, const TextureHolder &textures, Position p); 



        //Destructor
        virtual ~Tower() { }

        virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

        //Update the state of the tower, should be virtual
        virtual void Update() { }

        //Shoot an enemy, should be virtual
        virtual void Shoot() { }

        virtual unsigned int GetCategory() const override;

        // This sets the permission for the tower to move
        void SetMovePermission(bool permissionToMove);

        // Getter of permission to move
        bool CanMove() const;

        // Sets if the tower is moving, i.e., it is being moved by the player
        // returns true if the setting was succesful
        bool SetMoveState(bool state);

        // Tells if the tower is being moved by the player
        bool IsMoving() const;

        virtual sf::FloatRect GetBoundingRect() const;

    protected:
        Textures::ID ToTextureID(Type type);
        Tower::Type type_;
        int range_;
        sf::Sprite sprite_;
        bool canMove_;
        bool isMoving_;
        Position position_;
        //enemies_in_range_;
        int reload_speed_;
        //Bullet bullet_type_;
};