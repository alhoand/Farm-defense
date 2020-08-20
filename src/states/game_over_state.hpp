#pragma once

#include "state.hpp"
#include "../container.hpp"
#include <SFML/Graphics.hpp>

class GameOverState : public State {
    public:
        GameOverState(StateStack& stack, Context context);
        virtual void    Draw();
        virtual bool    Update(sf::Time dt);
        virtual bool    HandleEvent(const sf::Event& event);

    private:
        sf::Text        gameOverText_;
        GUI::Container  GUIContainer_;
};