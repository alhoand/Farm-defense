#include "state.hpp"
#include <SFML/Graphics.hpp>

class PauseState : public State {
    public:
        PauseState(StateStack& stack, Context context);
        virtual void Draw();
        virtual bool Update(sf::Time dt);
        virtual bool HandleEvent(const sf::Event& event);

    private:
        sf::Sprite backgroundSprite_;
        sf::Text pausedText_;
        sf::Text instructionText_;
};