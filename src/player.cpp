#include "player.hpp"
#include <iostream>


Player::Player(sf::RenderWindow& window, sf::Vector2f viewOffset) 
    : window_(window), viewOffset_(viewOffset), lives_(10), status_() { }

// Adapted from SFML Game Development-book
void Player::HandleEvent(const sf::Event& event, CommandQueue& commands) {
    if (event.type == sf::Event::MouseButtonPressed) {
    }


}
//Adapted from the SFML Game Development-book
void Player::HandleRealtimeInput(CommandQueue& commands) {

}

void Player::ReduceLife()
{
    lives_--;
    std::cout << "Player lost one life, lives now: " << lives_ << std::endl;
}

int Player::GetLives()
{
    return lives_;
}

Player::GameStatus Player::GetGameStatus()
{
    return status_;
}

void Player::SetGameStatus(Player::GameStatus newStatus)
{
    status_ = newStatus;
}