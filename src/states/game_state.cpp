#include "game_state.hpp"
#include "../node_component.hpp"
#include "../resource_identifiers.hpp"
#include <memory>

GameState::GameState(StateStack& stack, Context context) :
    State(stack, context),
    gameField_(*context.window_, context.viewOffset_),
    player_(*context.player_),
    GUIContainer_(),
    GUIController_(*context.GUIController_)
    { 
        auto pauseButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_, sf::IntRect(108,0,55,53),sf::IntRect(0,0,55,54));
        pauseButton->setPosition(890, 10);
        pauseButton->SetType(GUI::ID::PlayPause);
        pauseButton->SetCallback([this] ()
	{
		RequestStackPush(States::ID::Pause);
	});
        GUIContainer_.Pack(pauseButton);

        //GetContext().textures_->Load(Textures::ID::FireTower, "../media/textures/tower.png");

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

    GUIController_.FetchInput(commands);

	return true;
}

bool GameState::HandleEvent(const sf::Event& event) {
    CommandQueue& commands = gameField_.GetCommandQueue();
    player_.HandleEvent(event, commands);
    if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P))
		RequestStackPush(States::ID::Pause);

    if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::U))
    {
        std::cout << "Requested upgrade " << std::endl;
        RequestStackPush(States::ID::Sidebar);
		RequestStackPush(States::ID::GameUpgradeTowerSideBar);
    }
    if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I))
    {
        std::cout << "Requested info " << std::endl;
        RequestStackPush(States::ID::Sidebar);
    }
        
    GUIContainer_.HandleEvent(event);
    return true;
}

