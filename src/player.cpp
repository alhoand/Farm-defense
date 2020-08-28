#include "player.hpp"
#include "towers/tower.hpp"
#include "tower_picture.hpp"
#include <iostream>


Player::Player(sf::RenderWindow& window, sf::Vector2f viewOffset) 
    : window_(window), viewOffset_(viewOffset), lives_(10), status_(), money_(500), currentLevel_(1), infoRequested_(false), infoPopRequested_(false) { }


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
                        RequestInfo();
                        std::cout <<"Info requested in tower"<< std::endl; 
                        if (tower.CanMove() && !tower.IsMoving())
                        {   
                            tower.setOrigin(mouse.x - (tower.getPosition().x - tower.getOrigin().x),
                                            mouse.y - (tower.getPosition().y - tower.getOrigin().y));
                            tower.setPosition(mouse.x,mouse.y);
                            tower.Move();
                        }
                   }else if(tower.IsActive() && !tower.IsColliding() && !tower.IsMoving())
                   {
                       SetPlacementSuccess();
                   }else if(!tower.IsColliding()) // If there was a click and tower is moving and not colliding
                   {
                        tower.Deactivate();
                        tower.DisallowMoving();
                        SetPlacementSuccess();
                        //ResetInfoRequestStatus();

                   }else
                   {
                       SetPlacementFailure();
                   }
                   
                }
                else //All towers that are not clicked
                {
                    //RequestInfoPop();
                    if (!tower.IsColliding())
                    {
                        tower.Deactivate();
                        if (tower.CanMove())
                        {
                            //tower.Stop();
                            tower.DisallowMoving();

                            SetPlacementSuccess();
                        }
                    }
                }
            });
        commands.Push(activate);


        //Sidebar tower picture click
        Command activateTowerPicture;
        activateTowerPicture.category_ = Category::TowerPicture;
        activateTowerPicture.action_ = DerivedAction<TowerPicture>([mouse, this] (TowerPicture& tp, sf::Time)
        {

            if (tp.GetBoundingRect().contains(mouse) && !tp.IsDragged() && !IsDragging())
            {
                if (tp.IsActive())
                {
                    sf::Vector2f parent = tp.GetWorldPosition() - tp.getPosition();
                    sf::Vector2f origin = tp.getOrigin();
                    tp.setOrigin(tp.getOrigin() +parent +origin); // Some black magic here
                    
                    //tp.setPosition(mouse - parent - origin);//sf::Vector2f(100.f, 100.f)); //- tp.GetClickPos()); //-  tp.GetSidebarPos() * 100.f - tp.GetClickPos()); //+ tp.GetSidebarPos());
                    tp.setPosition(mouse);
                    tp.Drag();
                    Drag();
                    

                }
                SetPlacementFailure();

                
            } 
        
        });
        commands.Push(activateTowerPicture);
        
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
void Player::HandleRealtimeInput(CommandQueue& commands) {
    // Check if the tower was succesfully placed / built
    if (PlacementSuccess())
    {
        Command deactivateTp;
        deactivateTp.category_ = Category::TowerPicture;
        deactivateTp.action_ = DerivedAction<TowerPicture>([this](TowerPicture& tp, sf::Time)
        {
            if (tp.IsDragged() && IsDragging())
            {
                if (PlacementSuccess())
                {
                    tp.GetBack();
                    SetPlacementFailure(); // Reset placement so that this block of code is not called all the time
                    ResetDragging();
                }else{
                }
            }
        });
        commands.Push(deactivateTp);
    }
}


bool Player::IsDragging() const
{
    return isDragging_;
}

void Player::Drag()
{
    isDragging_ = true;
}

void Player::ResetDragging()
{
    isDragging_ = false;
}

void Player::ReduceLife()
{
    lives_--;
    std::cout << "Player lost one life, lives now: " << lives_ << std::endl;
}

int Player::GetLives() const
{
    return lives_;
}

Player::GameStatus Player::GetGameStatus() const
{
    return status_;
}

void Player::SetGameStatus(Player::GameStatus newStatus)
{
    status_ = newStatus;
}

void Player::ResetGame()
{
    lives_ = 10;
    status_ = GameStatus::GameRunning; 
    money_ = 500;
    currentLevel_ = 1;
    isDragging_ = false;
}

int Player::GetPlayerMoney() const
{
    return money_;
}

void Player::AddMoney(int money)
{
    money_ += money;
}

int Player::GetCurrentLevel() const
{
    return currentLevel_;
}

void Player::AdvanceLevel()
{
    currentLevel_++;
}

bool Player::BuyTower(int price)
{
    if (money_ < price)
    {
        std::cout << "Cannot buy tower, not enough money" << std::endl;
        return false;
    }
    money_ -= price;
    return true;
}

bool Player::SellTower(int price)
{
    bool success = price>=0;
    if (success)
    {
        AddMoney(price);
    }
    return success;
}

bool Player::PlacementSuccess()
{
    return towerPlacementSuccess_;
}

bool Player::InfoRequested() const
{
    return infoRequested_;
}

bool Player::InfoPopRequested() const
{
    return infoPopRequested_;
}

void Player::ResetInfoRequestStatus()
{
    infoRequested_ = false;
}

void  Player::ResetInfoPopStatus()
{
    infoPopRequested_ = false;
}

void Player::RequestInfoPop()
{
    infoPopRequested_ = true;
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

void Player::RequestInfo()
{
    infoRequested_ = true;
}