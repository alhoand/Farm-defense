#pragma once

#include "bullet.hpp"
#include "../entity.hpp"
#include "../category.hpp"
#include "../data_tables.hpp"
#include "../label.hpp"
#include "range_node.hpp"

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
        Tower(Tower::Type type, const TextureHolder& textures);

        // Destructor
        ~Tower() { Tower::towerCount_--; }

        virtual void            DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

        //Update the state of the tower
        virtual void            UpdateCurrent(sf::Time dt, CommandQueue& commands) override;

        // Makes the tower shoot, that is, pushes shoot command to command queue
        void                    Shoot(CommandQueue& commands, sf::Vector2f direction);

        // Getters for category and range
        virtual unsigned int    GetCategory() const override;
        float                   GetRange() const;

        // NOTE: This is NOT GetCategory()!
        // - this represents the type of tower, not category. Category is related to commands!
        Tower::Type             GetType() const { return type_; }

        // These set the permission for the tower to move
        void                    AllowMoving();
        void                    DisallowMoving();

        void                    Activate();
        void                    Deactivate();

        bool                    IsMarkedForRemoval() const override;

        // Getter of permission to move
        bool                    CanMove() const;
        bool                    CanShoot() const;
        bool                    IsActive() const;

        // Sets the tower moving or to stop
        bool                    Move();
        void                    Stop();

        // Getter that tells if the tower is being moved by the player
        bool                    IsMoving() const;

        void                    Collides(bool collision = false);
        bool                    IsColliding() const;                    

        virtual sf::FloatRect   GetBoundingRect() const override;

        static Tower*           ActiveTower(); 

        static void             ActiveTower(std::unique_ptr<Tower> &ptr, CommandQueue& commands);

        static void             ActiveTower(Tower& tower, CommandQueue& commands);

        static int              TowerCount();

        bool                    MyRange(RangeNode*);


        bool                    IsColliding() { return isColliding_; }

        void                    Sell();
        bool                    IsSold() const;

    protected:

        void                    MakeTransparent();
        void                    MakeVisible();

        // Creates a bullet for the tower to shoot, is virtual, since this depends on tower type
        virtual void        CreateBullet(SceneNode& node, const TextureHolder& textures) const = 0;

        Tower::Type         type_;
        sf::Sprite          sprite_;
        float               range_;      // range of fire in units
        sf::Vector2f        direction_;  // where are the tower's guns pointed at, should ALWAYS be unit vector
        float               reloadTime_; // how often can the tower shoot (in seconds) 

        bool                canShoot_;
        bool                isSold_;
        static int          towerCount_;
        sf::Time            countdown_;
        Command             shootCommand_;

        unsigned int        isActive_;
        bool                canMove_;
        bool                isMoving_;
        RangeNode*          rangeCircle_;
        bool                isColliding_;
        bool                collisionCalled_;   
};