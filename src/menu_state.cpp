#include <menu_state.hpp>
#include <utility.hpp>
#include <resource_holder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context), options_(), optionIndex_(0)
{
	sf::Texture& texture = context.textures->Get(Textures::ID::TitleScreen);
	sf::Font& font = context.fonts->Get(Fonts::Main);

	backgroundSprite_.setTexture(texture);
    sf::Text playOption;
    playOption.setFont(font);
    playOption.setString("Play");
    CenterOrigin(playOption);
    playOption.setPosition(context.window->getView().getSize() / 2.f);
    options_.push_back(playOption);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	CenterOrigin(exitOption);
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
	options_.push_back(exitOption);

	UpdateOptionText();
}

void MenuState::Draw() {
	sf::RenderWindow& window = *GetContext().window;
	window.setView(window.getDefaultView());
	window.draw(backgroundSprite_);

	for (const sf::Text& text : options_)
		window.draw(text);
}

bool MenuState::Update() {
	return true;
}

bool MenuState::HandleEvent(const sf::Event& event) {
	// The demonstration menu logic
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Return) {
		if (optionIndex_ == Play) {
			RequestStackPop();
			RequestStackPush(States::Game);
		} else if (optionIndex_ == Exit) {
			// The exit option was chosen, by removing itself, the stack will be empty, and the game will know it is time to close.
			RequestStackPop();
		}
	}

	else if (event.key.code == sf::Keyboard::Up) {
		// Decrement and wrap-around
		if (optionIndex_ > 0)
			optionIndex_--;
		else
			optionIndex_ = options_.size() - 1;

		UpdateOptionText();
	}

	else if (event.key.code == sf::Keyboard::Down) {
		// Increment and wrap-around
		if (optionIndex_ < options_.size() - 1)
			optionIndex_++;
		else
			optionIndex_ = 0;

		UpdateOptionText();
	}

	return true;
}

void MenuState::UpdateOptionText() {
    if (options_.empty())
        return;
    // White all texts
    for (sf::Text& text : options_)
        text.setColor(sf::Color::White);
    // Red the selected text
    options_[optionIndex_].setColor(sf::Color::Red);
}