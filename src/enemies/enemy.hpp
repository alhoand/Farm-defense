#pragma once

//Initial header file for abstract enemy class
#include <vector>

#include "../bullet.hpp"
#include "../entity.hpp"
#include "../resource_identifiers.hpp"
#include "../command_queue.hpp"
#include "../animation.hpp"
//#include "../data_tables.hpp"

#include <SFML/Graphics/Sprite.hpp>


class Enemy : public Entity {
    public:
        //Enemy types
        enum Type {
            Fire,
            Water,
            Leaf,
            TypeCount //enumerators are indexed so last one tells the count of previous ones 
        };
    public:
                
                        Enemy(Type type, const TextureHolder &textures, float difficultyLevel, float travelledDistance, int directionIndex);
        virtual         ~Enemy();

        void            DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
        unsigned int    GetCategory() const override; // might also be made virtual later, but not now
        sf::FloatRect   GetBoundingRect() const override;
        float             GetSpeed() const;
        bool            IsMarkedForRemoval() const override;

    protected:
        virtual void    UpdateMovementPattern(sf::Time dt); //can be made virtual later, not necessary now
        void            UpdateCurrent(sf::Time dt, CommandQueue& commands) override;
        virtual void    CheckDestroyBehaviour(CommandQueue& commands);

        Textures::ID    ToTextureID(Enemy::Type type);

        Type            type_;
        sf::Sprite      sprite_;
        float           travelledDistance_;
		std::size_t     directionIndex_;
        float           difficultyLevel_;
        int             speed_;
        bool            isMarkedForRemoval_;
        bool            showDeathAnimation_;
        Animation       deathAnimation_;
};
