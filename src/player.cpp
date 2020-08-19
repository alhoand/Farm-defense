#include "player.hpp"
#include "towers/tower.hpp"


Player::Player(sf::RenderWindow& window, sf::Vector2f viewOffset) : window_(window), viewOffset_(viewOffset) { }

// Adapted from SFML Game Development-book

void Player::HandleEvent(const sf::Event& event, CommandQueue& commands) {
    // Refactor this to the Controller class if needed
    if (event.type == sf::Event::MouseButtonPressed) {
        Command activate;
        activate.category_ = Category::Tower;
        sf::Vector2f mouse = window_.mapPixelToCoords(sf::Vector2i(event.mouseButton.x,event.mouseButton.y), window_.getView());
        //sf::Vector2f mouse = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));
        activate.action_ = DerivedAction<Tower> (
           [event, &commands, mouse] (Tower& tower, sf::Time dt) {
               if (tower.GetBoundingRect().contains(sf::Vector2f(event.mouseButton.x,event.mouseButton.y))) {
                   std::cout << "Tower was clicked!" << std::endl;
                   if (!tower.IsActive())
                   {
                        Tower::ActiveTower(tower, commands);
                        if (tower.CanMove() && !tower.IsMoving())
                        {   
                                std::cout << "Click " << mouse.x << ", " << mouse.y << std::endl;
                                std::cout << tower.getOrigin().x << ", " << tower.getOrigin().y << std::endl;
                                tower.setOrigin(mouse.x - (tower.GetWorldPosition().x - tower.getOrigin().x),
                                mouse.y - (tower.GetWorldPosition().y - tower.getOrigin().y));
                                std::cout << tower.getOrigin().x << ", " << tower.getOrigin().y << std::endl;
                            //tower.setPosition(mouse.x,mouse.y);
                            //tower.Move();
                        }else if(tower.IsMoving()){
                            //tower.Stop();
                            std::cout << "the tower was moving" <<std::endl;
                        }
                   }else
                   {
                       tower.Deactivate();
                       tower.Stop();
                       //tower.DisallowMoving();
                   }
                    
                }//else 
                /*{
                    tower.Deactivate();
                    tower.Stop();
                }*/
           }
        );
        commands.Push(activate);
    }
    if (event.type == sf::Event::MouseMoved)
    {
        Command move;
        move.category_ = Category::Active;
        sf::Vector2f mouse = window_.mapPixelToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y), window_.getView());
        //sf::Vector2f mouse = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));
        move.action_ = DerivedAction<Tower> (
           [event, &commands, mouse] (Tower& tower, sf::Time dt) {
            //if (tower.GetBoundingRect().contains(sf::Vector2f(event.mouseMove.x,event.mouseMove.y))) {
                //std::cout << "Tower was clicked!" << std::endl;
                //Tower::ActiveTower(tower, commands);
                if (tower.IsMoving())
                {
                   // tower.setOrigin(mouse.x - (tower.GetWorldPosition().x - tower.getOrigin().x),
                     //       mouse.y - (tower.GetWorldPosition().y - tower.getOrigin().y));
                    //tower.setPosition(mouse.x,mouse.y);
                    std::cout << "mouse: " << mouse.x << ", " << mouse.y << std::endl;
                }
               /* else {
                    tower.Stop();
                    tower.Deactivate();          
                }*/
           });
        commands.Push(move);

    }
    /*
    if (event.type == sf::Event::MouseButtonReleased)
    {
        Command output;
        output.category_ = Category::Active;
        output.action_ = DerivedAction<Tower>(
                [=](Tower& tower, sf::Time) {
                    if (tower.IsMoving()) {
                        tower.Stop();
                    }
                });
        commands.Push(output);

    }*/


}
//Adapted from the SFML Game Development-book
void Player::HandleRealtimeInput(CommandQueue& commands) {

}