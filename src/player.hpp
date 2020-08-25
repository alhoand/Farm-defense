#pragma once
#include "command_queue.hpp"
#include "category.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

class Player {
    public:
                            Player(sf::RenderWindow& window, sf::Vector2f viewOffset);

        void                HandleEvent(const sf::Event& event, CommandQueue& commands);
        void                HandleRealtimeInput(CommandQueue& commands);
        bool                PlacementSuccess();
    private:
        void                SetPlacementSuccess();
        void                SetPlacementFailure();
        sf::RenderWindow&   window_;
        sf::Vector2f        viewOffset_;
        bool                towerPlacementSuccess_;
};