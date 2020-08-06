#include "game_state.hpp"

GameState::GameState(StateStack& stack, Context context) 
            : State(stack, context),
             gameField_(*context.window_, context.viewOffset_),
             player_(*context.player_) { }

void GameState::Draw() {
    gameField_.Draw(); // calls the gamefield to draw everything
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

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
		RequestStackPush(States::ID::Pause);

    return true;
}

