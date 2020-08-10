#include "pause_state.hpp"
#include "../resource_holder.hpp"
#include "../button.hpp"
#include <cmath>

PauseState::PauseState(StateStack& stack, Context context): 
	State(stack, context), 
	backgroundSprite_(), 
	pausedText_(), 
	instructionText_(), 
	GUIContainer_(context)
	{
	sf::Font& font = context.fonts_->Get(Fonts::Main);
	sf::Vector2f viewSize = context.window_->getView().getSize();

	pausedText_.setFont(font);
	pausedText_.setString("Game Paused");	
	pausedText_.setCharacterSize(70);
	
	//center origin of text
	sf::FloatRect bounds = pausedText_.getLocalBounds();
	pausedText_.setOrigin(::floor(bounds.left + bounds.width / 2.f), std::floor(50 + bounds.top + bounds.height / 2.f));
	pausedText_.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	auto resumeButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_,Textures::ID::ResumeButtonNormal,Textures::ID::ResumeButtonSelected);
	resumeButton->setPosition(10, 10);
	resumeButton->SetCallback([this] ()
	{
		RequestStackPop();
	});
	GUIContainer_.Pack(resumeButton);

	auto menuButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
	menuButton->setPosition(550, 300);
	menuButton->SetText("Menu");
	menuButton->SetCallback([this] ()
	{
		RequestStateClear();
        RequestStackPush(States::ID::Menu);
	});
	GUIContainer_.Pack(menuButton);

	auto quitButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
	quitButton->setPosition(550, 400);
	quitButton->SetText("Ragequit");
	quitButton->SetCallback([this] ()
	{
		RequestStateClear();
	});
	GUIContainer_.Pack(quitButton);
}

void PauseState::Draw() {
    sf::RenderWindow& window = *GetContext().window_;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(sf::Vector2f(window.getSize()));

    window.draw(backgroundShape);
    window.draw(pausedText_);
    window.draw(GUIContainer_);
}

bool PauseState::Update(sf::Time) {
	return false;
}

bool PauseState::HandleEvent(const sf::Event& event) {
	
	GUIContainer_.HandleEvent(event);
	
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