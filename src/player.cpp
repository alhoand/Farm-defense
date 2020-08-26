#include "player.hpp"
#include "towers/tower.hpp"
#include "tower_picture.hpp"
#include <iostream>


Player::Player(sf::RenderWindow& window, sf::Vector2f viewOffset) 
    : window_(window), viewOffset_(viewOffset), lives_(10), status_(), score_(0) { }

// Adapted from SFML Game Development-book

void Player::HandleEvent(const sf::Event& event, CommandQueue& commands) {
    if (event.type == sf::Event::MouseButtonPressed) // CLICK
    {
        // If the player clicks on a tower, send a message to all towers
        Command activate;
        activate.category_ = Category::Tower;
        sf::Vector2f mouse = window_.mapPixelToCoords(sf::Vector2i(event.mouseButton.x,event.mouseButton.y), window_.getView());
        activate.action_ = DerivedAction<Tower> ( [&commands, mouse, this] (Tower& tower, sf::Time)
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

                   }else if(!tower.IsColliding()) // If there was a click and tower is moving and not colliding
                   {
                        tower.Deactivate();
                        tower.DisallowMoving();
                        SetPlacementSuccess();
                        //std::cout << "Placement success was set" << std::endl;

                   }else
                   {
                       //std::cout << "Placement failure was set" << std::endl;
                       SetPlacementFailure();
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
                                //std::cout << "Placement success was set" << std::endl;

                                SetPlacementSuccess();
                            }
                       }
                }
            }
            );
        commands.Push(activate);


        //Sidebar tower picture click
        Command activateTowerPicture;
        activateTowerPicture.category_ = Category::TowerPicture;
        activateTowerPicture.action_ = DerivedAction<TowerPicture>([mouse, this] (TowerPicture& tp, sf::Time)
        {
            if (tp.GetBoundingRect().contains(mouse) && !tp.IsDragged())
            {
                std::cout << "TowerPicture was pressed!"<< std::endl;

                sf::Vector2f parent = tp.GetWorldPosition() - tp.getPosition();
                sf::Vector2f origin = tp.getOrigin();
                std::cout << "parent pos: " << parent.x << ", "  << parent.y << std::endl;
                tp.setOrigin(tp.getOrigin() +parent +origin); // Some black magic here
                
                //tp.setPosition(mouse - parent - origin);//sf::Vector2f(100.f, 100.f)); //- tp.GetClickPos()); //-  tp.GetSidebarPos() * 100.f - tp.GetClickPos()); //+ tp.GetSidebarPos());
                tp.setPosition(mouse);
                tp.Drag();
                SetPlacementFailure();
                
            }
    
            //std::cout << "Click:TowerPic origin:" << tp.getOrigin().x << ", " << tp.getOrigin().y << std::endl;
            //std::cout << "Click:TowerPic world pos:" << tp.GetWorldPosition().x << ", " << tp.GetWorldPosition().y << std::endl;
            //std::cout << "Click:TowerPic pos:" << tp.getPosition().x << ", " << tp.getPosition().y << std::endl;
            //std::cout << "TowerPic Getpos:" << tp.GetPosition().x << ", " << tp.GetPosition().y << std::endl;
        
        });
        commands.Push(activateTowerPicture);

    }
    if (event.type == sf::Event::MouseButtonReleased)
    {
        Command deactivateTp;
        deactivateTp.category_ = Category::TowerPicture;
        deactivateTp.action_ = DerivedAction<TowerPicture>([this](TowerPicture& tp, sf::Time)
        {
            if (tp.IsDragged())
            {
                if (PlacementSuccess())
                {
                    //std::cout << "The tower pic was kindly asked to go back to the sidabar" << std::endl;
                    tp.UnDrag();
                    tp.GetBack();
                }else{
                    //std::cout << "Cannot be placed here!" << std::endl;
                }
            }
        });
        commands.Push(deactivateTp);
    }

    if (event.type == sf::Event::MouseMoved)
    {
        Command move;
        move.category_ = Category::Active; // Goes only to active towers
        sf::Vector2f mouse = window_.mapPixelToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y));
        //std::cout << "Mouse: " << mouse.x << ", " << mouse.y << std::endl;
        move.action_ = DerivedAction<Tower> (
           [mouse] (Tower& tower, sf::Time) {
                if (tower.IsMoving())
                    tower.setPosition(mouse.x,mouse.y);
           });

        commands.Push(move);
        // MOVE the tower pictures that reside in the sidebar
        Command movePic;
        movePic.category_ = Category::TowerPicture;
        //mouse = window_.mapPixelToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y), window_.getView());
        movePic.action_ = DerivedAction<TowerPicture>([mouse](TowerPicture& tp, sf::Time)
        {
            if (tp.IsDragged())
            {
                tp.setPosition(mouse);
            }
        });
        commands.Push(movePic);

    }

}
//Adapted from the SFML Game Development-book
void Player::HandleRealtimeInput(CommandQueue&) {
    // Do nothing
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


// Used to tell the GUI that there was a successfull placement of a tower
void Player::SetPlacementSuccess()
{
    towerPlacementSuccess_ = true;
}

void Player::SetPlacementFailure()
{
    towerPlacementSuccess_ = false;
}

bool Player::PlacementSuccess()
{
    return towerPlacementSuccess_;
}

void Player::SetGameStatus(Player::GameStatus newStatus)
{
    status_ = newStatus;
}

int Player::GetScore()
{
    return score_;
}

void Player::SetScore(int change)
{
    score_ += change; // test if this works with negative change, or does it have to?
}

void Player::SetPlayerName(sf::String name)
{
    name_ = name;
}
sf::String Player::GetPlayerName()
{
    return name_;
}