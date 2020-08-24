#pragma once

#include "bullet.hpp"
#include "../game_field.hpp"

/* Bomb class is derived class of bullet, with some extra features.
 * A bomb is shot by bombing towers, and it
 * - has a range of 100, hits enemies within this range
 * - has damage of 10 hp
 * - has speed of 100
 */

class Bomb : public Bullet {
    public:
        // The constructor
        Bomb(const TextureHolder& textures);

        // Getter for bomb's range
        int GetRange();
        
        // Boolean to indicate whether the bomb has been detonated
        bool IsDetonated();

        void UpdateCurrent(sf::Time dt,CommandQueue& commands);

        // Detonate function tells the bomb to detonate, that is, push detonate command to command queue
        void Detonate(CommandQueue& commands);

    private:
        int             distance_;          // the distance the bomb will travel before detonating
        int             range_;             // the range within which enemies will be hit
        float           travelledDistance_; // how far the bomb has already travelled
        Command         detonateCommand_;
        bool            isDetonated_;         
};