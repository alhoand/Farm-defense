#include "state.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class MenuState : public State {
    public:
        MenuState(StateStack& stack, Context context);
        virtual void Draw();
        virtual bool Update();
        virtual bool HandleEvent(const sf::Event& event);

        void UpdateOptionText();

    private:
        enum OptionNames {
            Play,
            Exit,
        };

        sf::Sprite backgroundSprite_;
        std::vector<sf::Text> options_;
        std::size_t optionIndex_;
};