#pragma once

#include "bullet.hpp"
#include "../game_field.hpp"

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