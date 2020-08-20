#pragma once

#include "bullet.hpp"
#include "../game_field.hpp"

/* This is a bomb, shot by bombing towers, that
 * - has a range of 100, hits enemies within this range
 * - has damage of 10 hp
 * - has speed of 100
 */

class Bomb : public Bullet {
    public:
        Bomb(const TextureHolder& textures);

        int GetRange();
        bool IsDetonated();

        void UpdateCurrent(sf::Time dt,CommandQueue& commands);

        void Detonate(CommandQueue& commands);

    private:
        // we have type_, sprite_, speed_ and damage_ by Bullet
        int             distance_;          // the distance the bomb will travel before detonating
        int             range_;             // the range within which enemies will be hit
        float           travelledDistance_; // how far the bomb has already travelled
        Command         detonateCommand_;
        bool            isDetonated_;         
};