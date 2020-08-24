#pragma once
#include "command_queue.hpp"
#include "category.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

class Player {
    public:
        enum GameStatus
		{
			GameRunning,
			GameWon,
			GameLost
		};

    public:
        Player(sf::RenderWindow& window, sf::Vector2f viewOffset);

        void        HandleEvent(const sf::Event& event, CommandQueue&);
        void        HandleRealtimeInput(CommandQueue&);
        void        ReduceLife();
        int         GetLives();
        GameStatus  GetGameStatus();
        void        SetGameStatus(GameStatus newStatus);
        int         GetScore();
        void        SetScore(int change);

    private:
        sf::RenderWindow&   window_;
        sf::Vector2f        viewOffset_;
        int                 lives_;
        GameStatus          status_;
        int                 score_;
};