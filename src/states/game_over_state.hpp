#pragma once

#include "state.hpp"
#include "../container.hpp"
#include "../player.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

//#include <string>

class GameOverState : public State {
    public:
        GameOverState(StateStack& stack, Context context);
        virtual void    Draw();
        virtual bool    Update(sf::Time dt);
        virtual bool    HandleEvent(const sf::Event& event);

    private:
        sf::Text        gameOverText_;
        GUI::Container  GUIContainer_;
        sf::Time        elapsedTime_;
        sf::String      typedText_;
        sf::Text        text_;
        sf::String        name_;
        Player          player_;
};