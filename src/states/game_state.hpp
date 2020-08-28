#pragma once

#include <vector>
#include <list>

#include "../game_field.hpp"
#include "../player.hpp"
#include "state.hpp"
#include "../container.hpp"

class GameState : public State {
public:
    GameState(StateStack& stack, Context context);
    virtual void Draw() override;
    virtual bool Update(sf::Time dt) override;
    virtual bool HandleEvent(const sf::Event& event) override;

private:
    void            IncreasePlayerMoney(int amount);

    GameField       gameField_;
    Player&         player_;
    GUI::Container  GUIContainer_;
    GUI::Controller& GUIController_;
    bool            gameEnded_;
};