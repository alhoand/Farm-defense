#include "application.hpp"
#include "utility.hpp"
#include "state.hpp"
#include "state_identifiers.hpp"
#include "title_state.hpp"
#include "game_state.hpp"
#include "menu_state.hpp"
#include "pause_state.hpp"

/* Application::Application()
: window_(sf::VideoMode(640, 480), "States", sf::Style::Close), textures_(), fonts_(), player_(),
  stateStack_(State::Context(window_, textures_, fonts_, player_)), statisticsText_(), 
  statisticsUpdateTime_(), statisticsNumFrames_(0) {
	window_.setKeyRepeatEnabled(false);

	fonts_.Load(Fonts::Main, "Media/Sansation.ttf");
	textures_.Load(Textures::ID::TitleScreen, "Media/Textures/TitleScreen.png");

	statisticsText_.setFont(fonts_.Get(Fonts::Main));
	statisticsText_.setPosition(5.f, 5.f);
	statisticsText_.setCharacterSize(10u);

	RegisterStates();
	stateStack_.PushState(States::ID::Title);
}
*/

void Application::Run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window_.isOpen()) {
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			ProcessInput();
			Update(TimePerFrame);

			// Check inside this loop, because stack might be empty before update() call
			if (stateStack_.IsEmpty())
				window_.close();
		}

		UpdateStatistics(dt);
		Render();
	}
}

void Application::RegisterStates() {
    stateStack_.RegisterState<TitleState>(States::ID::Title);
    stateStack_.RegisterState<MenuState>(States::ID::Menu);
    stateStack_.RegisterState<GameState>(States::ID::Game);
    stateStack_.RegisterState<PauseState>(States::ID::Pause);
}

void Application::ProcessInput() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        stateStack_.HandleEvent(event);
    }

    // if (event.type == sf::Event::Closed)
	// window_.close();
}

void Application::Update(sf::Time dt) {
    stateStack_.Update(dt);
}

void Application::Render() {
	// window_.clear();

	stateStack_.Draw();

	// window_.setView(window_.GetDefaultView());
	// window.Draw(statisticsText_);

	// window_.display();
}

void Application::UpdateStatistics(sf::Time dt) {
	statisticsUpdateTime_ += dt;
	statisticsNumFrames_ += 1;
	if (statisticsUpdateTime_ >= sf::seconds(1.0f)){
		statisticsText_.setString("FPS: " + toString(statisticsNumFrames_));
		statisticsUpdateTime_ -= sf::seconds(1.0f);
		statisticsNumFrames_ = 0;
	}
}