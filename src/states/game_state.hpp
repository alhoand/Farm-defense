#pragma once


#include "../game_field.hpp"
#include "../player.hpp"
#include "state.hpp"


class GameState : public State {
public:
    GameState(StateStack& stack, Context context);
    virtual void Draw() override;
    virtual bool Update(sf::Time dt) override;
    virtual bool HandleEvent(const sf::Event& event) override;

private:
    GameField gameField_;
    Player& player_;

};