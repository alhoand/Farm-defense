#include "game_state.hpp"

GameState::GameState(StateStack& stack, Context context)
: State(stack, context), gameField_(*context.window), player_(*context.player) { }

void GameState::Draw() {
	gameField_.Draw();
}

bool GameState::Update(sf::Time dt) {
	gameField_.Update(dt);

	CommandQueue& commands = gameField_.GetCommandQueue();
	player_.HandleRealtimeInput(commands);

	return true;
}

bool GameState::HandleEvent(const sf::Event& event) {
	// Game input handling
	CommandQueue& commands = gameField_.GetCommandQueue();
	player_.HandleEvent(event, commands);

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		RequestStackPush(States::Pause);

	return true;
}