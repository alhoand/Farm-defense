#include "game_state.hpp"
#include "../button.hpp"
#include "../resource_identifiers.hpp"
#include "../data_tables.hpp"

namespace {
	const std::vector<GUIData> table = InitializeGUIData();
}

GameState::GameState(StateStack& stack, Context context) :
    State(stack, context),
    gameField_(*context.window_, context.viewOffset_),
    player_(*context.player_),
    GUIContainer_(context)
    { 
        player_.SetGameStatus(Player::GameRunning);
        
        auto pauseButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_, table[GUIitems::ID::PauseButton].normalTexture, table[GUIitems::ID::PauseButton].selectedTexture);
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
    ModifyPlayerScore(gameField_.GetRoundScore());
    
    if (gameField_.HasNewEnemiesReachedEnd())
    {
        player_.ReduceLife();
    }
    if (player_.GetLives() <= 0) // Somehow the winning case
    {
        player_.SetGameStatus(Player::GameLost);
        RequestStackPush(States::ID::GameOver);
        return false;
    }
    if (!gameField_.HasEnemiesToSpawn() && gameField_.EndOfLevel())
    {
        player_.SetGameStatus(Player::GameWon);
        RequestStackPush(States::ID::GameOver);
        return false;
    }

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


void GameState::ModifyPlayerScore(int score)
{
    player_.SetScore(score);
    //std::cout << "current score: " << player_.GetScore() << std::endl;
}

