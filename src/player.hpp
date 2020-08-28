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

        void        HandleEvent(const sf::Event& event, CommandQueue&);
        void        HandleRealtimeInput(CommandQueue&);
        void        ReduceLife();
        int         GetLives() const;
        GameStatus  GetGameStatus() const;
        void        SetGameStatus(GameStatus newStatus);
        void        ResetGame();
        int         GetPlayerMoney() const;
        void        AddMoney(int money);
        int         GetCurrentLevel() const;
        void        AdvanceLevel();
        bool        BuyTower(int price);
        bool        SellTower(int price);
        bool        PlacementSuccess();
        bool        InfoRequested() const;
        bool        InfoPopRequested() const;
        void        ResetInfoRequestStatus();
        void        ResetInfoPopStatus();
        bool        IsDragging() const;
        void        Drag();
        void        ResetDragging();

        void        RequestInfoPop();
        
    private:
        void        SetPlacementSuccess();
        void        SetPlacementFailure();
        void        RequestInfo();

        
        
        sf::RenderWindow&   window_;
        sf::Vector2f        viewOffset_;
        int                 lives_;
        GameStatus          status_;
        int                 money_;
        int                 currentLevel_;
        bool                towerPlacementSuccess_;
        bool                infoRequested_;
        bool                infoPopRequested_;
        bool                isDragging_;

};