#include <state_stack.hpp>
#include <SFML/Graphics.hpp>
#include <state_identifiers.hpp>

class TitleState : public State {
    public:
        TitleState(StateStack& stack, Context context);
        virtual void Draw();
        virtual bool Update(sf::Time dt);
        virtual bool HandleEvent(const sf::Event& event);

    private:
        sf::Sprite backgroundSprite_;
        sf::Text text_;
        bool showText_;
        sf::Time textEffectTime_;
};