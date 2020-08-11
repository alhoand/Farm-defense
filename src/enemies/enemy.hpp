#pragma once

//Initial header file for abstract enemy class
#include <vector>

#include "../bullet.hpp"
#include "../entity.hpp"
#include "../resource_identifiers.hpp"
#include "../command_queue.hpp"
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
        //Constructors
        //Enemy();
            
        Enemy(Type type, const TextureHolder &textures, int hp = 50, float speed=50.f, float travelledDistance = 0.f, int directionIndex = 0, float difficultyLevel = 1);
        virtual ~Enemy();

        void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

        unsigned int GetCategory() const override; // might also be made virtual later, but not now
        sf::FloatRect GetBoundingRect() const override;
        bool IsMarkedForRemoval() const override;

    protected:
        virtual void UpdateMovementPattern(sf::Time dt) = 0; //can be made virtual later, not necessary now
        void UpdateCurrent(sf::Time dt, CommandQueue& commands) override;
        virtual void CheckDestroyBehaviour(CommandQueue& commands);

        Textures::ID ToTextureID(Enemy::Type type);

        Type type_;
        sf::Sprite sprite_;
        float travelledDistance_;
		std::size_t directionIndex_;
        float difficultyLevel_;
        int speed_;
        bool isMarkedForRemoval_;
        //std::vector<EnemyData> dataTable_;
};
