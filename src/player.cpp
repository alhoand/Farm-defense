#include "player.hpp"
#include "Ghost.hpp"


Player::Player(sf::RenderWindow& window, sf::Vector2f viewOffset) : window_(window), viewOffset_(viewOffset) { }


// Adapted from SFML Game Development-book
void Player::HandleEvent(const sf::Event& event, CommandQueue& commands) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouse = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));
        Command output;
        std::cout << "Mouse pressed" << std::endl;
  //      sf::Vector2i mouseInt = sf::Mouse::getPosition(window_);
  //      sf::Vector2f mouse(mouseInt.x + viewOffset_.x, mouseInt.y + viewOffset_.y);
        output.category_ = Category::Ghost;
        output.action_ = DerivedAction<Ghost>(
            [=] (Ghost& ghost, sf::Time dt) {
            });
        commands.Push(output);
    }

}
//Adapted from the SFML Game Development-book
void Player::HandleRealtimeInput(CommandQueue& commands) {
    Command output;
    //sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(window_));
    sf::Vector2f mouse = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));
 //  sf::Vector2f mouse(mouseInt.x + viewOffset_.x, mouseInt.y + viewOffset_.y);
    output.category_ = Category::Ghost;
    output.action_ = DerivedAction<Ghost>(
        [=] (Ghost& ghost, sf::Time dt) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                sf::FloatRect bounds = ghost.GetBounds();
                if (bounds.contains(mouse)) {
                    if (!ghost.GetClicked()){
                        ghost.setOrigin(mouse.x - (ghost.getPosition().x - ghost.getOrigin().x),
                                        mouse.y - (ghost.getPosition().y, ghost.getOrigin().y));
                        ghost.SetClicked(true);
                    }
                }
                if (ghost.GetClicked()) {
                    ghost.setPosition(mouse);
                }
            }else{
                ghost.SetClicked(false);
            }
        }
    );
    commands.Push(output);
}

            /*
                if (bounds.contains(mouse)){
                    if (tower.SetMoveState(true)){
                        tower.setOrigin(mouse.x - (tower.getPosition().x - tower.getOrigin().x),
                                        mouse.y - (tower.getPosition().y - tower.getOrigin().y));
                        std::cout << "tower was set moving..." << std::endl;
                    }else{
                        tower.SetMoveState(false);
                        std::cout << "tower was set to not move anymore" << std::endl;
                    }
                }*/