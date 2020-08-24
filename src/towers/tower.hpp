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

        // Destructor
        ~Tower() { }

        virtual void            DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

        //Update the state of the tower
        virtual void            UpdateCurrent(sf::Time dt, CommandQueue& commands);

        // Makes the tower shoot, that is, pushes shoot command to command queue
        void                    Shoot(CommandQueue& commands, sf::Vector2f direction);

        // Getters for type and range
        virtual unsigned int    GetCategory() const;
        float                   GetRange() const;

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

    protected:
        // A helper function to determine bullet's texture according to type
        Textures::ID        ToTextureID(Type type);
        // Creates a bullet for the tower to shoot, is virtual, since this depends on tower type
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