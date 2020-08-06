#include "title_state.hpp"
#include "utility.hpp"
#include "resource_holder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

TitleState::TitleState(StateStack& stack, Context context)
: State(stack, context), text_(), showText_(true), textEffectTime_(sf::Time::Zero) {
	backgroundSprite_.setTexture(context.textures->Get(Textures::ID::TitleScreen));
	text_.setFont(context.fonts->Get(Fonts::Main));
	text_.setString("Press any key to start");
	CenterOrigin(text_);
	text_.setPosition(context.window->getView().getSize() / 2.f);
}

bool TitleState::HandleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        RequestStackPop();
        RequestStackPush(States::ID::Menu);
    }
    return true;
}

void TitleState::Draw() {
	sf::RenderWindow& window = *GetContext().window;
	window.draw(backgroundSprite_);
	if (showText_)
		window.draw(text_);
}

bool TitleState::Update(sf::Time dt) {
    textEffectTime_ += dt;
    if (textEffectTime_ >= sf::seconds(0.5f)) {
        showText_ = !showText_;
        textEffectTime_ = sf::Time::Zero;
    }
    return true;
}