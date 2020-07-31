#include <application.hpp>

void Application::RegisterStates() {
    stateStack_.RegisterState<TitleState>(States::Title);
    stateStack_.RegisterState<MenuState>(States::Menu);
    stateStack_.RegisterState<GameState>(States::Game);
    stateStack_.RegisterState<PauseState>(States::Pause);
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