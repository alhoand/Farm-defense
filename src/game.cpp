#include "game.hpp"

// All this code is essentially from the book SFML Game Development
Game::Game() 
    : window_(sf::VideoMode(640, 480), "Tower Defense"), 
    player_(),
    timePerFrame_(sf::seconds(1.f / 60.f)),
    playerSpeed_(100.f) {
    player_.setRadius(40.f);
    player_.setPosition(100.f, 100.f);
    player_.setFillColor(sf::Color::Cyan);
}


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
    while (window_.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                HandlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                HandlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                window_.close();
                break;
        }
    }
}

void Game::HandlePlayerInput(sf::Keyboard::Key key,bool isPressed){  
    if (key == sf::Keyboard::W)
        isMovingUp_ = isPressed;
    else if (key == sf::Keyboard::S)
        isMovingDown_ = isPressed;
    else if (key == sf::Keyboard::A)
        isMovingLeft_ = isPressed;
    else if (key == sf::Keyboard::D)
        isMovingRight_ = isPressed;
}

void Game::Update(sf::Time deltaTime) {
    sf::Vector2f movement(0.f, 0.f);
    if (isMovingUp_)
        movement.y -= playerSpeed_;
    if (isMovingDown_)
        movement.y += playerSpeed_;
    if (isMovingLeft_)
        movement.x -= playerSpeed_;
    if (isMovingRight_)
        movement.x += playerSpeed_;

    player_.move(movement * deltaTime.asSeconds());
}

void Game::Render() {
    window_.clear();
    window_.draw(player_);
    window_.display();
}

