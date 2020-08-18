#include "state.hpp"
#include "../state_identifiers.hpp"
#include <SFML/Graphics/Rect.hpp>
#include "../resource_holder.hpp"
#include "../state_stack.hpp"
#include "title_state.hpp"
#include <cmath>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

TitleState::TitleState(StateStack& stateStack, Context context)
                : State(stateStack, context),
                backgroundSprite_(),
                logoSprite_(),
                text_() 
{
        backgroundSprite_.setTexture(context.textures_->Get(Textures::ID::TitleBackground));
        logoSprite_.setTexture(context.textures_->Get(Textures::ID::logo));
        logoSprite_.setPosition(120,50);
        text_.setFont(context.fonts_->Get(Fonts::ID::Title));
        text_.setString("Press any key to start");

        sf::FloatRect bounds = text_.getLocalBounds();
        text_.setOrigin(::floor(bounds.left + bounds.width / 2.f), ::floor(bounds.top + bounds.height / 2.f));
        //text_.setPosition(sf::Vector2f(context.window_->getSize() / 2u));
        text_.setPosition(sf::Vector2f(context.window_->getDefaultView().getSize().x/2.f, context.window_->getDefaultView().getSize().y/2.f));

        //std::cout << "Render size:" << context.window_->getSize().x << ", " << context.window_->getSize().y << std::endl;
}

bool TitleState::Update(sf::Time dt) {
    return true;
}

bool TitleState::HandleEvent(const sf::Event &event) {
	if (event.type == sf::Event::KeyReleased)
	{
		RequestStackPop();
		RequestStackPush(States::ID::Menu);
	}

	return true;
}

void TitleState::Draw() {
    sf::RenderWindow& window = *GetContext().window_;
    window.draw(backgroundSprite_);
    window.draw(logoSprite_);
    window.draw(text_);

}




