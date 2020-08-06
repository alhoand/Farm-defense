#include "pause_state.hpp"
#include "../resource_holder.hpp"
#include <cmath>

PauseState::PauseState(StateStack& stack, Context context)
: State(stack, context), backgroundSprite_(), pausedText_(), instructionText_() {
	sf::Font& font = context.fonts_->Get(Fonts::Main);
	sf::Vector2f viewSize = context.window_->getView().getSize();

	pausedText_.setFont(font);
	pausedText_.setString("Game Paused");	
	pausedText_.setCharacterSize(70);
	
	//center origin of text
	sf::FloatRect bounds = pausedText_.getLocalBounds();
	pausedText_.setOrigin(::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	
	pausedText_.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	instructionText_.setFont(font);
	instructionText_.setString("(Press Backspace to return to the main menu)");	

	//center instruction text
	bounds = instructionText_.getLocalBounds();
	instructionText_.setOrigin(::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));


	instructionText_.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void PauseState::Draw() {
    sf::RenderWindow& window = *GetContext().window_;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0,150));
    backgroundShape.setSize(sf::Vector2f(window.getSize()));

    window.draw(backgroundShape);
    window.draw(pausedText_);
    window.draw(instructionText_);
}

bool PauseState::Update(sf::Time) {
	return false;
}

bool PauseState::HandleEvent(const sf::Event& event) {
	if (event.type != sf::Event::KeyPressed)
		return false;

    // If esc is pressed, return to the game
	if (event.key.code == sf::Keyboard::P) {
		// Escape pressed, remove itself to return to the game
		RequestStackPop();
	}

    // If backspace is pressed, quit game and return to the main menu
    if (event.key.code == sf::Keyboard::BackSpace) {
        RequestStateClear();
        RequestStackPush(States::ID::Menu);
    }
    return false;
}