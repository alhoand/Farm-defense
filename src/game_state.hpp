#include "state.hpp"
#include "game_field.hpp"
#include "player.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class GameState : public State {
    public:
        GameState(StateStack& stack, Context context);
        virtual void Draw();
        virtual bool Update(sf::Time dt);
        virtual bool HandleEvent(const sf::Event& event);

    private:
        GameField gameField_;
        Player& player_;
};