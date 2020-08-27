#pragma once

#include "bullet.hpp"
#include "../game_field.hpp"
#include "../animation.hpp"

/* Bomb class is derived class of bullet, with some extra features.
 * A bomb is shot by bombing towers, and it
 * - has a range of 100, hits enemies within this range
 * - has damage of 10 hp
 * - has speed of 150
 */

class Bomb : public Bullet {
    public:
        // The constructor
        Bomb(const TextureHolder& textures);

        // Getter for bomb's range
        int GetRange();
        // Indicator that tells if bomb can detonate
        void Detonate();
        
        bool CanDetonate();
        bool HasDetonated();
        bool AnimationFinished();

        void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
        void UpdateCurrent(sf::Time dt,CommandQueue& commands);

    private:
        int             distance_;          // the distance the bomb will travel before detonating
        int             range_;             // the range within which enemies will be hit
        float           travelledDistance_; // how far the bomb has already travelled        
        bool            canDetonate_;       // Indicator that tells if bomb is travelled far enough and can detonate
        bool            hasDetonated_;

        Animation       hitAnimation_;
};