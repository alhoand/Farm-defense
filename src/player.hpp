#pragma once
#include "command_queue.hpp"
#include "category.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

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

        void                HandleEvent(const sf::Event& event, CommandQueue&);
        void                HandleRealtimeInput(CommandQueue&);
        void                ReduceLife();
        int                 GetLives();
        GameStatus          GetGameStatus();
        void                SetGameStatus(GameStatus newStatus);
        int                 GetScore();
        void                SetScore(int change);
        void                SetPlayerName(sf::String name);
        sf::String          GetPlayerName();
        bool                PlacementSuccess();
        bool                InfoRequested() const;
        bool                InfoPopRequested() const;
        void                ResetInfoRequestStatus();
        void                ResetInfoPopStatus();

        void                RequestInfoPop();
    private:
        void                SetPlacementSuccess();
        void                SetPlacementFailure();
        void                RequestInfo();

        
        
        sf::RenderWindow&   window_;
        sf::Vector2f        viewOffset_;
        int                 lives_;
        GameStatus          status_;
        int                 score_;
        sf::String          name_;
        bool                towerPlacementSuccess_;
        bool                infoRequested_;
        bool                infoPopRequested_;

};