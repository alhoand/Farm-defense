#include "game.hpp"
#include <iostream>

// All this code is essentially from the book SFML Game Development
Game::Game() 
    : window_(sf::VideoMode(1024,768), "Tower Defense", sf::Style::Close),
    viewOffset_(200.f, 0.f), 
    gameField_(window_, viewOffset_),
    timePerFrame_(sf::seconds(1.f / 60.f)),
    player_(window_)
    { }

void Game::Run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (window_.isOpen()) {
        ProcessInput();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > timePerFrame_)
        {
            timeSinceLastUpdate -= timePerFrame_;
            ProcessInput();
            Update(timePerFrame_);
        }
        Render();
    }
}
void Game::ProcessInput() { 

    CommandQueue& commands = gameField_.GetCommandQueue();
    
    sf::Event event;
	while (window_.pollEvent(event)) {
        player_.HandleEvent(event, commands);

        if (event.type == sf::Event::Closed) {
            window_.close();
        }
        if (event.type == sf::Event::GainedFocus)
            isPaused_ = false;
            
        else if (event.type == sf::Event::LostFocus)
            isPaused_ = true;
    }
    player_.HandleRealtimeInput(commands);
}

void Game::Update(sf::Time deltaTime) {
    if (!isPaused_)
        gameField_.Update(deltaTime); // updates the gamefield on each tick

}

void Game::Render() {
    window_.clear();
    gameField_.Draw(); // calls the gamefield to draw everything
    window_.setView(window_.getDefaultView()); // not necessary right now 
    window_.display();
}

