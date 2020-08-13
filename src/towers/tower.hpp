#pragma once

//Initial header file for abstract tower class
#include "bullet.hpp"

#include "../scene_node.hpp"
#include "../enemies/enemy.hpp"
#include "../category.hpp"
#include "../entity.hpp"
#include "../resource_identifiers.hpp"
#include "../command_queue.hpp"
#include "../data_tables.hpp"

class Tower : public Entity {
    public:
        enum Type {
            Basic,
            Advanced,
            Super,
            TypeCount
        };

        Tower();

        // Another constructor, inherited classes use this
        Tower(Tower::Type type, const TextureHolder& textures, float range, float reloadTime);

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
        virtual void        CreateBullet(SceneNode& node, const TextureHolder& textures) const = 0;

        Tower::Type         type_;
        sf::Sprite          sprite_;
        // Range of fire in units
        float               range_;
        // Where are the tower's guns pointed at, should ALWAYS be unit vector
        sf::Vector2f        direction_;
        // How often can the tower shoot (in seconds)
        float               reloadTime_;

        bool                canShoot_;

        //Bullet::Type        bulletType_;

        sf::Time            countdown_;
        Command             shootCommand_;
};