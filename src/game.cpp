#include "game.hpp"
#include <iostream>

// All this code is essentially from the book SFML Game Development
Game::Game() 
    : window_(sf::VideoMode(1024,768), "Tower Defense", sf::Style::Close), 
    gameField_(window_),
    timePerFrame_(sf::seconds(1.f / 60.f))
    { }

void Game::Run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (window_.isOpen()) {
        ProcessEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > timePerFrame_)
        {
            timeSinceLastUpdate -= timePerFrame_;
            ProcessEvents();
            Update(timePerFrame_);
        }
        Render();
    }
}
void Game::ProcessEvents() { 
    sf::Event event;
	while (window_.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				//handlePlayerInput(event.key.code, true);
				break;

			case sf::Event::KeyReleased:
				//handlePlayerInput(event.key.code, false);
				break;

			case sf::Event::Closed:
				window_.close();
				break;
		}
    }
}

void Game::Update(sf::Time deltaTime) {

    gameField_.Update(deltaTime); // updates the gamefield on each tick

}

void Game::Render() {
    window_.clear();
    gameField_.Draw(); // calls the gamefield to draw everything
    window_.setView(window_.getDefaultView()); // not necessary right now 
    window_.display();
}

