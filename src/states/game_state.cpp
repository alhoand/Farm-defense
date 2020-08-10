#include "game_state.hpp"
#include "../button.hpp"
#include "../resource_identifiers.hpp"

GameState::GameState(StateStack& stack, Context context) :
    State(stack, context),
    gameField_(*context.window_, context.viewOffset_),
    player_(*context.player_),
    GUIContainer_(context)
    { 
        auto pauseButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_,Textures::ID::PauseButtonNormal,Textures::ID::PauseButtonSelected);
        pauseButton->setPosition(10, 10);
        pauseButton->SetCallback([this] ()
	{
		RequestStackPush(States::ID::Pause);
	});
    GUIContainer_.Pack(pauseButton);
    }

void GameState::Draw() {
    gameField_.Draw(); // calls the gamefield to draw everything
    sf::RenderWindow& window = *GetContext().window_;
    window.draw(GUIContainer_);
}

bool GameState::Update(sf::Time dt) {
    gameField_.Update(dt); // updates the gamefield on each tick

    CommandQueue& commands = gameField_.GetCommandQueue();
	player_.HandleRealtimeInput(commands);

	return true;
}

bool GameState::HandleEvent(const sf::Event& event) {
    CommandQueue& commands = gameField_.GetCommandQueue();
    player_.HandleEvent(event, commands);

    if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P))
		RequestStackPush(States::ID::Pause);

    GUIContainer_.HandleEvent(event);
    return true;
}

