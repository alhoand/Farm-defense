#pragma once

#include "bullet.hpp"

#include "../command_queue.hpp"
#include "../utility.hpp"

/* Tower class is a abstract class with multiple inherited classes:
 * - basic tower
 * - super tower
 * - slowing tower
 * - bombing tower
 */

class Tower : public Entity {
    public:
        enum Type {
            Basic,
            Slowing,
            Super,
            Bombing,
            TypeCount
        };

        // Constructor, used by inherited classes
        Tower(Tower::Type type, const TextureHolder& textures, float range, float reloadTime);

        //Destructor
        ~Tower() { }

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
        float               range_;      // range of fire in units
        sf::Vector2f        direction_;  // where are the tower's guns pointed at, should ALWAYS be unit vector
        float               reloadTime_; // how often can the tower shoot (in seconds) 
        bool                canShoot_;
        sf::Time            countdown_;
        Command             shootCommand_;
};