#include "state.hpp"
#include "state_identifiers.hpp"
#include <SFML/Graphics/Rect.hpp>
#include "resource_holder.hpp"
#include "state_stack.hpp"
#include "title_state.hpp"
#include <cmath>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

TitleState::TitleState(StateStack& stateStack, Context context)
                : State(stateStack, context),
                backgroundSprite_(),
                text_() 
{
        backgroundSprite_.setTexture(context.textures_->Get(Textures::ID::TitleBackground));
        text_.setFont(context.fonts_->Get(Fonts::ID::Title));

        text_.setString("Press any key to start");

        sf::FloatRect bounds = text_.getLocalBounds();
        text_.setOrigin(::floor(bounds.left + bounds.width / 2.f), ::floor(bounds.top + bounds.height / 2.f));
        text_.setPosition(sf::Vector2f(context.window_->getSize() / 2u));
}

bool TitleState::Update(sf::Time dt) {
    return true;
}

bool TitleState::HandleEvent(const sf::Event &event) {
    
    if (event.type == sf::Event::KeyReleased) {
        std::cout << "A key was pressed" << std::endl;
        RequestStackPop();
        RequestStackPush(States::ID::Game); // Goes to game directly
    }
    return true;
}

void TitleState::Draw() {
    sf::RenderWindow& window = *GetContext().window_;
    window.draw(backgroundSprite_);

    window.draw(text_);

}




