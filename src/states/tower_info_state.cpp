#include "../resource_holder.hpp"
#include "../button.hpp"
#include "../label.hpp"
#include "../towers/tower.hpp"
#include <cmath>
#include "tower_info_state.hpp"
#include <memory>
#include <string>
#include <iostream>
#include "../utility.hpp"
#include <cassert>
#include "../command_queue.hpp"
#include "../player.hpp"
namespace {
    auto towerData = InitializeTowerData();
}

TowerInfoState::TowerInfoState(StateStack& stack, Context context) :
    State(stack, context),
    backgroundSprite_(),
    backgroundShape_(),
    titleText_(),
    descriptionText_(),
    sellButton_(),
    viewSize_(context.window_->getView().getSize().x/4.f, context.window_->getView().getSize().y),
    GUIContainer_(),
    GUIController_(*context.GUIController_)
    {
        
        //std::cout << "Upgrade tower state constructor" << std::endl;

        // Initialize the tower's name title
        titleText_ = std::make_shared<GUI::Label>("", *context.fonts_, 40, Fonts::Main);
        titleText_->CenterTextOrigin();
        titleText_->setPosition(viewSize_.x/2.f, 100.f);
        GUIContainer_.Pack(titleText_, true);
        
        // Initialize tower info text
        descriptionText_ = std::make_shared<GUI::Label>("", *context.fonts_, 20, Fonts::Main);
        descriptionText_->CenterTextOrigin();
        descriptionText_->setPosition(viewSize_.x/2.f, 420.f);
        GUIContainer_.Pack(descriptionText_, true);

    // Initialize the sell button
        sellButton_ = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
        sellButton_->setOrigin(sellButton_->GetGlobalBounds().width/2.f, sellButton_->GetGlobalBounds().height/2.f);
        sellButton_->setPosition(viewSize_.x/2.f, 200.f);
        sellButton_->SetText("");
        sellButton_->SetCallback([this] ()
        {
            Command command;
            command.category_ = Category::Active;
            auto player = GetContext().player_;
            command.action_ = DerivedAction<Tower>([player](Tower& t, sf::Time)
            {
                if (!t.IsMoving())
                {
                    t.Destroy();
                    player->RequestInfoPop();
                    
                }
            });
            GUIController_.SendCommand(command);
        });
        GUIContainer_.Pack(sellButton_, true);


        //Initialize the back button
        auto backButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
        backButton->setOrigin(backButton->GetGlobalBounds().width/2.f, backButton->GetGlobalBounds().height/2.f);
        backButton->setPosition(viewSize_.x/2.f, 400.f);
        backButton->SetText("Return");
        backButton->SetCallback([this] ()
	    {
            Command command;
            command.category_ = Category::Active;
            auto player = GetContext().player_;
            command.action_ = DerivedAction<Tower>([player](Tower& t, sf::Time)
            {
                if (!t.IsMoving())
                {
                    player->RequestInfoPop();
                    t.Deactivate();
                    
                }
            });
            GUIController_.SendCommand(command);
	    });
        GUIContainer_.Pack(backButton, true);

        // Here is the upgrade button if implemented in the future
        /*
        auto upgradeButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
        upgradeButton->setOrigin(upgradeButton->GetGlobalBounds().width/2.f, upgradeButton->GetGlobalBounds().height/2.f);
        upgradeButton->setPosition(viewSize_.x/2.f, 500.f);
        upgradeButton->SetText("Upgrade");
        upgradeButton->SetCallback([this] ()
        {
            std::cout << "The active tower upgrade button was pressed:  " << std::endl;
            Command command;
            command.category_ = Category::Active;
            command.action_ = DerivedAction<Tower>([] (Tower&, sf::Time)
            {
                std::cout << "The active tower upgrade command was read in the active tower.  " << std::endl;
                //t.rp;
            });
            GUIController_.SendCommand(command);

	    });
        GUIContainer_.Pack(upgradeButton, true);
*/ 

        // Make the pause button available in this state as well
        auto pauseButton = GetContext().GUIContainer_->GetChild(GUI::ID::PlayPause);
        GUIContainer_.Pack(pauseButton);

        backgroundShape_.setFillColor(sf::Color(160,82,45,230));
        //backgroundShape_.setFillColor(sf::Color(0,0,235,230));
        backgroundShape_.setSize(viewSize_);
        GUIContainer_.setPosition(context.window_->getView().getSize().x - viewSize_.x, 0);
        backgroundShape_.setPosition(GUIContainer_.getPosition());
    }

void TowerInfoState::Draw() {
    sf::RenderWindow& window = *GetContext().window_;
    window.setView(window.getDefaultView());

    window.draw(backgroundShape_);
    window.draw(GUIContainer_);
    //window.draw(pla)
}

TowerInfoState::~TowerInfoState()
{
   // std::cout << "U deleted" <<std::endl;
    //GetContext().player_->ResetInfoPopStatus();
}

bool TowerInfoState::Update(sf::Time dt) {
    UpdateGUI(dt);
    UpdateTowerInfo();
    auto player = GetContext().player_;
    if (player->InfoRequested()){
        player->ResetInfoRequestStatus();
    }
	return true;
}

void TowerInfoState::UpdateGUI(sf::Time dt) {

    if (GetContext().player_->InfoPopRequested())
    {
        RequestStackPop(); // Pop this state
        RequestStackPush(States::ID::Sidebar); // Push the sidebar back
        GetContext().player_->ResetInfoPopStatus(); // Reset the request status
        // << "State popped and pushed" << std::endl;
        return;
    }

    GUIContainer_.Update(dt);

}


void TowerInfoState::UpdateTowerInfo()
{
    Command command;
    command.category_ = Category::Active;
    GUI::Label::Ptr titleText = titleText_;
    GUI::Label::Ptr descriptionText = descriptionText_;
    GUI::Button::Ptr sellButton = sellButton_;
    auto data = towerData;
    
    command.action_ = DerivedAction<Tower>([titleText, descriptionText, data, sellButton] (Tower& t, sf::Time) 
    {
        titleText->SetText(data[t.GetType()].name);
        sf::Vector2u pos(t.GetWorldPosition());
        // Maybe some logic: if the towers could be damaged, then "in mint condition" or "almost a wreck"
        /*descriptionText->SetText("  HP: " + std::to_string(t.GetHitpoints())
            + "\n  " + std::to_string(pos.x) + ", " + std::to_string(pos.y)
        );*/ 
        sellButton->SetText("Sell for " + std::to_string(data[t.GetType()].sellPrice));

        //std::cout << "use count of ttitle text " << titleText.use_count() << std::endl;

    });
    
    GUIController_.SendCommand(command);
}


bool TowerInfoState::HandleEvent(const sf::Event& event) {
	if (!GUIContainer_.HandleEvent(event))
    {
        //std::cout << "Here we are at false" << std::endl;
        return false;
    }
    //std::cout << "Upgrade tower state here we are" << std::endl;
	    // Make the mouse-related events available for all
    if ((event.type == sf::Event::MouseMoved) || (event.type == sf::Event::MouseButtonPressed) || (event.type == sf::Event::MouseButtonReleased))
    {
        
        if (event.type == sf::Event::MouseButtonPressed)
        {
           // std::cout << "Mouse clicked event upgrade" <<std::endl;
            if (!backgroundShape_.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
            {
                Player* player = GetContext().player_;
                Command popCommand;
                popCommand.category_ = Category::Type::Tower;
                popCommand.action_ = DerivedAction<Tower>(
                            [player] (Tower&, sf::Time)
                            {
                                std::cout << "Pop command given" << std::endl;
                                
                                player->RequestInfoPop();

                                //player->Re
                                //NextEnemyWave();  //AddTower(towerButton->GetTowerType(), towerButton->GetClickPosition());  
                            }
                );
                GUIController_.SendCommand(popCommand);
                Command resetCommand;
                resetCommand.category_ = Category::Active;
                resetCommand.action_ = DerivedAction<Tower>(
                            [player] (Tower&, sf::Time)
                            {
                                std::cout << "Reset infopop command given" << std::endl;
                                
                                player->ResetInfoPopStatus();
                                //player->Re
                                //NextEnemyWave();  //AddTower(towerButton->GetTowerType(), towerButton->GetClickPosition());  
                            }
                );
                GUIController_.SendCommand(resetCommand);
                //std::cout << GUIContainer_.GetGlobalBounds().left <<", " << GUIContainer_.GetGlobalBounds().width << std::endl;
                //RequestStackPop();
                //RequestStackPush(States::ID::Sidebar);
            }else{
                return false; // This stops the clicks and moves propagating to lowers states, including game state            
            }
            
        }   

        return true; // Propagate other mouse-related events
    }

    if (event.type == sf::Event::KeyReleased)
    {
        return false;
    }
        
   /* // Deprecated:: If I is pressed, make the sidebar go away
	if ((event.type ==sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::U))
    {
       // std::cout << "KeyPressed" << std::endl;
		RequestStackPop();
        RequestStackPop();
    }*/


    //If p is pressed, go to Pause state
    if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::P))
    {
		RequestStackPush(States::ID::Pause);
	}
    /*if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::I))
    {
        std::cout << "Upgrade: I-KeyPressed" << std::endl;
		RequestStackPop();
        //RequestStackPush(States::ID::Sidebar);
    }*/

    //Otherwise, don't propagate the events
    return false;
}

//Helper function

