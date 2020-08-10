#ifndef ENEMY_HPP
#define ENEMY_HPP

//Initial header file for abstract enemy class
#include <vector>

#include "../bullet.hpp"
#include "../entity.hpp"
#include "../resource_identifiers.hpp"
#include "../command_queue.hpp"

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
        Enemy();
            
        Enemy(Type type, const TextureHolder &textures, float travelledDistance = 0.f, int directionIndex = 0);

        void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

        unsigned int GetCategory() const override;
        virtual sf::FloatRect GetBoundingRect() const override;
        bool IsMarkedForRemoval() const override;

    protected:
        void UpdateMovementPattern(sf::Time dt);
        virtual void UpdateCurrent(sf::Time dt, CommandQueue& commands) override;
        void CheckDestroyAbility(Enemy::Type type, CommandQueue& commands);

        Textures::ID ToTextureID(Enemy::Type type);

        Type type_;
        sf::Sprite sprite_;
        float travelledDistance_;
		std::size_t directionIndex_;
        int speed_;
        bool isMarkedForRemoval_;
        Command spawnFireEnemyCommand_;
};

#endif // ENEMY_HPP
