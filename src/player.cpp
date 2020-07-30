#include "player.hpp"
#include "tower.hpp"


Player::Player(sf::RenderWindow& window, sf::Vector2f viewOffset) : window_(window), viewOffset_(viewOffset) { }


// This is adapted from SFML Game Development-book
void Player::HandleEvent(sf::Event& event, CommandQueue& commands) {
    if (event.type == sf::Event::MouseButtonPressed) {
        Command output;
        std::cout << "Mouse pressed" << std::endl;
        sf::Vector2i mouseInt = sf::Mouse::getPosition(window_);
        sf::Vector2f mouse(mouseInt.x + viewOffset_.x, mouseInt.y + viewOffset_.y);

        output.category_ = Category::Tower;
        output.action_ = DerivedAction<Tower>(
            [=] (Tower& tower, sf::Time dt) {
                sf::FloatRect bounds = tower.GetBoundingRect();
                std::cout << "tower bounds height: " << bounds.height << " width: " << bounds.width << std::endl;
                std::cout << "tower pos x: " << tower.getPosition().x << " y: " << tower.getPosition().y << std::endl;
                std::cout << "mouse pos x: " << mouse.x << " y: " << mouse.y << std::endl;

                // If the mouse is on the sprite and the tower is permitted to move
                if (bounds.contains(mouse) && tower.CanMove()) {
                    std::cout << "mouse in bounds" << std::endl;
                    std::cout << "tower can move" << std::endl;
                    if (!tower.IsMoving()){
                        // This origin part is adapted from https://gamedev.stackexchange.com/questions/97060/moving-a-sprite-using-mouse-in-sfml-setorigin-logic-needed
                        tower.setOrigin(mouse.x - (tower.getPosition().x - tower.getOrigin().x),
                                        mouse.y - (tower.getPosition().y - tower.getOrigin().y));
                        tower.SetMoveState(true); // Set the tower to follow the mouse
                        std::cout << "tower was set moving..." << std::endl;
                    } else {
                        tower.SetMoveState(false); // "Set the tower to stay put"
                        std::cout << "tower was set to not move anymore" << std::endl;
                    }
                }
        });
        commands.Push(output);
    }

}
//Adapted from the SFML Game Development-book
void Player::HandleRealtimeInput(CommandQueue& commands) {
    Command output;
    //sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(window_));
    sf::Vector2i mouseInt = sf::Mouse::getPosition(window_);
    sf::Vector2f mouse(mouseInt.x + viewOffset_.x, mouseInt.y + viewOffset_.y);
    output.category_ = Category::Tower;
    output.action_ = DerivedAction<Tower>(
        [=] (Tower& tower, sf::Time dt) {
            if (tower.CanMove() && tower.IsMoving()) {
                std::cout << tower.getPosition().x << ","<< tower.getPosition().y << std::endl;
                tower.setPosition(mouse);
            }
        }
    );
    commands.Push(output);
}