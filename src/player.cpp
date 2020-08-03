#include "player.hpp"
#include "tower.hpp"


Player::Player(sf::RenderWindow& window) : window_(window), viewOffset_() { }


// Adapted from SFML Game Development-book
void Player::HandleEvent(const sf::Event& event, CommandQueue& commands) {
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

                if (bounds.contains(mouse)){
                    if (tower.SetMoveState(true)){
                        tower.setOrigin(mouse.x - (tower.getPosition().x - tower.getOrigin().x),
                                        mouse.y - (tower.getPosition().y - tower.getOrigin().y));
                        std::cout << "tower was set moving..." << std::endl;
                    }else{
                        tower.SetMoveState(false);
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