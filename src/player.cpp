#include "player.hpp"
#include "towers/tower.hpp"


Player::Player(sf::RenderWindow& window, sf::Vector2f viewOffset) : window_(window), viewOffset_(viewOffset) { }

// Adapted from SFML Game Development-book

void Player::HandleEvent(const sf::Event& event, CommandQueue& commands) {
    // Refactor this to the Controller class if needed
    if (event.type == sf::Event::MouseButtonPressed)
    {
        Command activate;
        activate.category_ = Category::Tower;
        sf::Vector2f mouse = window_.mapPixelToCoords(sf::Vector2i(event.mouseButton.x,event.mouseButton.y), window_.getView());
        //sf::Vector2f mouse = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));
        activate.action_ = DerivedAction<Tower> (
           [&commands, mouse] (Tower& tower, sf::Time dt)
            {
               if (tower.GetBoundingRect().contains(mouse))
                {
                  if (!tower.IsActive() && !tower.IsColliding())
                   {
                        Tower::ActiveTower(tower, commands);
                        if (tower.CanMove() && !tower.IsMoving())
                        {   
                            tower.setOrigin(mouse.x - (tower.getPosition().x - tower.getOrigin().x),
                                            mouse.y - (tower.getPosition().y - tower.getOrigin().y));
                            tower.setPosition(mouse.x,mouse.y);
                            tower.Move();
                        }

                   }else if(!tower.IsColliding())
                   {
                        tower.Deactivate();
                        tower.DisallowMoving();
                   }
                }
                else //All towers that are not clicked
                {
                    if (!tower.IsColliding())
                       {
                            tower.Deactivate();
                            if (tower.CanMove())
                            {
                                //tower.Stop();
                                tower.DisallowMoving();
                            }
                       }
                }
            }
            );
        commands.Push(activate);
    }
    
    if (event.type == sf::Event::MouseMoved)
    {
        Command move;
        move.category_ = Category::Active; // Goes only to active towers
        sf::Vector2f mouse = window_.mapPixelToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y));
        move.action_ = DerivedAction<Tower> (
           [mouse] (Tower& tower, sf::Time dt) {
                if (tower.IsMoving())
                    tower.setPosition(mouse.x,mouse.y);
           });

        commands.Push(move);

    }

}
//Adapted from the SFML Game Development-book
void Player::HandleRealtimeInput(CommandQueue& commands) {

}