#pragma once

#include "../towers/bullet.hpp"
#include "../entity.hpp"
#include "../resource_identifiers.hpp"
#include "../command_queue.hpp"
#include "../animation.hpp"
#include "../data_tables.hpp"
#include "../category.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <vector>

class Enemy : public Entity {
    public:
        //Enemy types
        enum Type {
            Basic,
            Bulk,
            Multiplying,
            Fast,
            TypeCount //enumerators are indexed so last one tells the count of previous ones 
        };
    public:
                
                        Enemy(Type type, const TextureHolder& texturesxtures, unsigned int difficultyLevel, float travelledDistance, int directionIndex);
        virtual         ~Enemy();

        void            DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
        unsigned int    GetCategory() const override; 
        sf::FloatRect   GetBoundingRect() const override;
        virtual float   GetSpeed() const; // some enemies can resist slowing down so can be redefined in derived class
        void            SlowDown(); 
        virtual void    TakeHit(int damage, unsigned int bulletType) = 0; // some enemies resist or take more damage if bullet is certain type, so that can be defined in derived classes
        bool            IsMarkedForRemoval() const override;
        int             GetScorePoints();

    protected:
        virtual void    UpdateMovementPattern(sf::Time dt); 
        void            UpdateCurrent(sf::Time dt, CommandQueue& commands) override;
        void            UpdateMovementAnimation(sf::Time dt);
        virtual bool    CheckDestroyBehaviour(sf::Time dt, CommandQueue& commands);
        float           DifficultyCoefficient() const;

        Type            type_;
        sf::Sprite      sprite_;
        float           travelledDistance_;
		std::size_t     directionIndex_;
        unsigned int    difficultyLevel_;
        float           difficultyIncrement_;
        int             maxSpeed_;
        bool            isSlowedDown_;
        float           slowDownRate_;
        bool            isMarkedForRemoval_;
        bool            showDeathAnimation_;
        bool            hasMovementAnimation_;
        Animation       deathAnimation_;
        Animation       movementAnimation_;
        bool            isGivenScorepoints_;
};
