#ifndef TOWER_DEF_GAME
#define TOWER_DEF_GAME

#include <SFML/Graphics.hpp>
#include "game_field.hpp"
#include "player.hpp"

class Game {
public:
    Game();
    void Run();
private:
    void ProcessInput();
    void Update(sf::Time deltaTime);
    void Render();
    void HandlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    sf::RenderWindow window_;
    sf::Vector2f viewOffset_;
    GameField gameField_;
    Player player_;
    
    bool isMovingUp_;
    bool isMovingDown_;
    bool isMovingLeft_;
    bool isMovingRight_;
    const sf::Time timePerFrame_;
    bool isPaused_ = false;
   // const float playerSpeed_;

};

#endif