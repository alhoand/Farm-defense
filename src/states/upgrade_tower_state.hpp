#include "state.hpp"
#include "../container.hpp"
#include <SFML/Graphics.hpp>
#include "../label.hpp"

class UpgradeTowerState : public State {
    public:
        UpgradeTowerState(StateStack& stack, Context context);
        virtual void Draw();
        virtual bool Update(sf::Time dt);
        virtual bool HandleEvent(const sf::Event& event);

    private:
        void UpdateGUI(sf::Time dt);
        sf::Sprite backgroundSprite_;
        sf::RectangleShape backgroundShape_;
        GUI::Label::Ptr titleText_;
        GUI::Label::Ptr descriptionText_;
        sf::Vector2f viewSize_;
        GUI::Container  GUIContainer_;
};