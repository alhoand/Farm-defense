#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void Run();
private:
    void ProcessEvents();
    void Update(sf::Time deltaTime);
    void Render();
    void HandlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    sf::RenderWindow window_;
    sf::CircleShape player_;
    bool isMovingUp_;
    bool isMovingDown_;
    bool isMovingLeft_;
    bool isMovingRight_;
    const sf::Time timePerFrame_;
    const float playerSpeed_;

};