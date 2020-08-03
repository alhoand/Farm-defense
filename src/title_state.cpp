#include "title_state.hpp"
#include <cmath>

TitleState::TitleState(StateStack& stateStack, Context context)
                : State(stateStack, context),
                backgroundSprite_(),
                text_() 
    {
        backgroundSprite_.setTexture(context.textures_->Get(Textures::ID::TitleBackground));
        text_.setFont(context.fonts_->Get(Fonts::ID::Title));

        text_.setString("Press any key to start");
        //To be refactored away to a utility file
        sf::FloatRect bounds = text_.getLocalBounds();
        text_.setOrigin(::floor(bounds.left + bounds.width / 2.f), ::floor(bounds.top + bounds.height / 2.f));
        text_.setPosition(sf::Vector2f(context.window_->getSize() / 2u));

    }


