#include "state.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class TitleState : public State {

public:
    TitleState(StateStack& stack_, Context context);

    virtual void Draw() override;

    virtual bool Update(sf::Time dt) override;

    virtual bool HandleEvent(const sf::Event& event) override;

private:
    sf::Sprite backgroundSprite_, logoSprite_;
    sf::Text text_;

    //bool showText_;
    //sf::Time textEffectTime_;


};