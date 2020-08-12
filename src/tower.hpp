#pragma once

//Initial header file for abstract tower class
#include "scene_node.hpp"
#include "bullet.hpp"
#include "enemies/enemy.hpp"
#include "category.hpp"
#include "entity.hpp"
#include "resource_identifiers.hpp"
#include "command_queue.hpp"
#include "data_tables.hpp"

class Tower : public Entity {
    public:
        enum Type {
            Fire,
            Water,
            Leaf,
            TypeCount
        };

        //Constructors

        // Default constructor - is it needed?
        Tower();

        // The constructor we want to use - uses data tables in order to determine the attributes' values
        Tower(Tower::Type type, const TextureHolder &textures);
        
        // The constructor for now. Most of the parameters should be given automatically, 
        // depending on type (inherited class)
        //Tower(Type type, const TextureHolder &textures, float range, int reloadSpeed, Bullet::Type bulletType, CommandQueue& commands);

        //Destructor
        virtual                 ~Tower() { };
        virtual void            DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

        //Update the state of the tower, should be virtual
        virtual void            UpdateCurrent(sf::Time dt, CommandQueue& commands) override;

        // Helper function
        void                    Shoot(CommandQueue& commands, sf::Vector2f direction);
        virtual unsigned int    GetCategory() const override;

        // This sets the permission for the tower to move
        // for now: this maybe is a clumsy way to achieve this
        void                    SetMovePermission(bool permissionToMove);

        // Getter of permission to move
        bool                    CanMove() const;
        bool                    CanShoot() const;

        // Sets the tower moving with state=true, stops with state=false.
        // Returns true if setting was succesful
        bool                    SetMoveState(bool state);

        // Getter that tells if the tower is being moved by the player
        bool                    IsMoving() const;
        virtual sf::FloatRect   GetBoundingRect() const override;
        float                   GetRange() const;

    protected:
        Textures::ID        ToTextureID(Type type);
        void                CreateBullet(SceneNode& node, const TextureHolder& textures) const;

        // There is velocity_ in Entity which, in this case, describes the rotational speed
        // Helper that makes textures::ID-types from Tower::Types
        Tower::Type         type_;
        // Range of fire in units
        float               range_;
        sf::Sprite          sprite_;
        // Where are the tower's guns pointed at (also gives direction for the bullet), should ALWAYS be unit vector
        sf::Vector2f        direction_;
        // Some kind of container for enemies in range - this could also be a function that is called every tick
        //std::vector<Enemy>  enemiesInRange_;
        float               reloadTime_;
        bool                canShoot_;

        //Bullet::Type        bulletType_;
        int                 bulletType_; //doesn't work anymore with Bullet::Type
        // bool isShooting_; not needed?
        sf::Time            countdown_;
        //CommandQueue&   commands_;
        Command             shootCommand_;
};