#pragma once

#include "state.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>


class EndOfLevelState : public State {
    public:
        EndOfLevelState(StateStack& stack, Context context);
        virtual void    Draw();
        virtual bool    Update(sf::Time dt);
        virtual bool    HandleEvent(const sf::Event& event);

    private:
        sf::Text        levelOverText_;
        sf::Time        elapsedTime_;
};