#pragma once
#include "command_queue.hpp"
#include "category.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

class Player {
public:
    Player(sf::RenderWindow& window, sf::Vector2f viewOffset);

    void HandleEvent(const sf::Event& event, CommandQueue& commands);
    void HandleRealtimeInput(CommandQueue& commands);
private:
    sf::RenderWindow& window_;
    sf::Vector2f viewOffset_;
};