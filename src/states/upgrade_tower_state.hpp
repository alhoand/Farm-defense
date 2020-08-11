#include "state.hpp"
#include "../container.hpp"
#include <SFML/Graphics.hpp>

class UpgradeTowerState : public State {
    public:
        UpgradeTowerState(StateStack& stack, Context context);
        virtual void Draw();
        virtual bool Update(sf::Time dt);
        virtual bool HandleEvent(const sf::Event& event);

    private:
        sf::Sprite backgroundSprite_;
        sf::Text titleText_;
        sf::Text descriptionText_;
        sf::Vector2f viewSize_;
        GUI::Container  GUIContainer_;
};