#pragma once

#include "../entity.hpp"
#include "../data_tables.hpp"
#include "../category.hpp"

#include <SFML/Graphics/Sprite.hpp>

/* Towers shoot bullets according to their type. 
 * Bullet class is a abstract class with multiple inherited classes:
 * - basic bullet
 * - super bullet
 * - bomb
 */

class Bullet : public Entity {
    public:
        enum Type {
            Basic,
            Super,
            Bomb,
            TypeCount
        };

    public:
        // Constructor to be used with inherited classes
        Bullet(Type type, const TextureHolder& textures);

        //Destructor
        ~Bullet() { }

        // Getters for the bullet's attributes
        float           GetSpeed() const;
        int             GetDamage() const;
        unsigned int    GetCategory() const;

        virtual sf::FloatRect GetBoundingRect() const;

    private:
        virtual void    UpdateCurrent(sf::Time dt, CommandQueue& commands);
        virtual void    DrawCurrent(sf::RenderTarget& target,sf::RenderStates states) const;

    protected:
        Type            type_;
        sf::Sprite      sprite_;
        float           speed_;
        int             damage_;
};