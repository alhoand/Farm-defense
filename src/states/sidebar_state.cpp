#include "sidebar_state.hpp"
#include "../command_queue.hpp"
#include "../game_field.hpp"
#include "../player.hpp"
#include "../tower_button.hpp"
#include "../data_tables.hpp"
#include <memory>
#include <string>

namespace
{
    const std::vector<TowerData> towerTable = InitializeTowerData();
}

SidebarState::SidebarState(StateStack& stack, Context context)
    : State(stack, context)
    , backgroundSprite_()
    , backgroundShape_()
    , titleText_(nullptr)
    , lifeText_(nullptr)
    , moneyText_(nullptr)
    , infoText_(nullptr)
    , towerTitle_(nullptr)
    , viewSize_(context.window_->getView().getSize().x/4.f, context.window_->getView().getSize().y)
    , GUIContainer_() 
    , GUIController_(*context.GUIController_)
    , towerPosition_(sf::Vector2f(viewSize_.x/2.f, 425.f))
    , sidebarWorld_(*context.window_,towerPosition_)
    , showInfotext_(false)
    , elapsedTime_(sf::Time::Zero)
    , towerTexts_()
    {
        GUIContainer_.setPosition(context.window_->getView().getSize().x - viewSize_.x, 0);
        sidebarWorld_.SetGraphPosition(GUIContainer_.getTransform());

        titleText_ = std::make_shared<GUI::Label>("Level: 1", *context.fonts_, 30, Fonts::Main);
        titleText_->setPosition(context.window_->getView().getSize().x-viewSize_.x + 10.f, 10.f);
        titleText_->SetColor(sf::Color(236,212,182));

        lifeText_ = std::make_shared<GUI::Label>("Lives: "+ std::to_string(GetContext().player_->GetLives()), *context.fonts_, 30, Fonts::Main);
        lifeText_->setPosition(context.window_->getView().getSize().x-viewSize_.x + 10.f, 45.f);
        lifeText_->SetColor(sf::Color(236,212,182));

        moneyText_ = std::make_shared<GUI::Label>("Money: " + std::to_string(GetContext().player_->GetPlayerMoney()), *context.fonts_, 30, Fonts::Main);
        moneyText_->setPosition(context.window_->getView().getSize().x-viewSize_.x + 10.f, 80.f);
        moneyText_->SetColor(sf::Color(236,212,182));

        infoText_ = std::make_shared<GUI::Label>("", *context.fonts_, 20, Fonts::Main);
        infoText_->SetColor(sf::Color(246,62,0), true);
        //infoText_->SetColor(sf::Color(206,21,0), true);

        infoText_->setPosition(context.window_->getView().getSize().x-(viewSize_.x/2), 685.f);
        infoText_->SetText(" ");

        auto levelButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
        levelButton->setOrigin(levelButton->GetGlobalBounds().width/2.f, levelButton->GetGlobalBounds().height/2.f);
        levelButton->setPosition(viewSize_.x/2.f, 175.f);
        levelButton->SetText("Start level");
        levelButton->SetCallback([this, levelButton] ()
        {
            Command nextLevelCommand;
            nextLevelCommand.category_ = Category::Type::GameField;
            nextLevelCommand.gameFieldAction_ = GameFieldAction(
                [this, levelButton] (GameField& gameField, sf::Time)
                {    
                    gameField.NextEnemyWave();
                }
            );
            GUIController_.SendCommand(nextLevelCommand);
        });

        auto retryButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_, sf::IntRect(0,374,200,88),sf::IntRect(0,550,200,88));
        retryButton->setOrigin(retryButton->GetGlobalBounds().width/2.f, retryButton->GetGlobalBounds().height/2.f);
        retryButton->setPosition(viewSize_.x/2.f, 275.f);
        retryButton->SetText("Retry game");
        retryButton->SetCallback([this] ()
        {
            GetContext().player_->ResetGame();
            RequestStackPop();
            RequestStackPop();
            RequestStackPush(States::ID::Game);
            RequestStackPush(States::ID::Sidebar);
        });
        
        GUIContainer_.Pack(levelButton, true);
        GUIContainer_.Pack(retryButton, true);

        towerTitle_ = std::make_shared<GUI::Label>("", *context.fonts_, 35, Fonts::Main);
        towerTitle_->setPosition(context.window_->getView().getSize().x-(viewSize_.x/2), 350.f);
        towerTitle_->SetText("Buy Towers");
        towerTitle_->SetColor(sf::Color(236,212,182));

        AddTowerButton(Tower::Type::Basic, -75.f, 0.f, sf::IntRect(55,53,83,83),sf::IntRect(55,53,83,83), *context.fonts_);
        AddTowerButton(Tower::Type::Slowing, +75.f, 0.f,sf::IntRect(55,53,83,83),sf::IntRect(55,53,83,83), *context.fonts_);
        AddTowerButton(Tower::Type::Bombing, -75.f, 150.f, sf::IntRect(55,53,83,83),sf::IntRect(55,53,83,83), *context.fonts_);
        AddTowerButton(Tower::Type::Super, +75.f, 150.f, sf::IntRect(55,53,83,83),sf::IntRect(55,53,83,83), *context.fonts_);

        backgroundShape_.setFillColor(sf::Color(160,82,45,235));
        backgroundShape_.setSize(viewSize_);

        backgroundShape_.setPosition(GUIContainer_.getPosition());

        std::cout << "end of sidebar constructor" << std::endl;
    }

void SidebarState::Draw() {
    sf::RenderWindow& window = *GetContext().window_;
    window.setView(window.getDefaultView());

    window.draw(backgroundShape_);
    window.draw(*titleText_);
    window.draw(*lifeText_);
    window.draw(*moneyText_);
    window.draw(*infoText_);
    window.draw(*towerTitle_);
    window.draw(GUIContainer_);
    for (auto it = towerTexts_.begin(); it != towerTexts_.end(); it++)
    {
        window.draw(**it);
    }
    sidebarWorld_.Draw();
}

bool SidebarState::Update(sf::Time dt) {
    if (showInfotext_) 
    {
        infoText_->SetText("Not enough money to buy tower");
        moneyText_->SetColor(sf::Color(246,62,0));
        elapsedTime_ += dt;
    } 
    if (elapsedTime_ >= sf::seconds(13))
    {
        showInfotext_ = false;
        elapsedTime_ = sf::Time::Zero;
        infoText_->SetText("", false);
        moneyText_->SetColor(sf::Color(236,212,182));
    }

    UpdateGUI(dt);
    GetContext().player_->HandleRealtimeInput(sidebarWorld_.GetCommandQueue());
	return true;
}

void SidebarState::UpdateGUI(sf::Time dt) {
    titleText_->SetText("Level: " + std::to_string(GetContext().player_->GetCurrentLevel()), false);
    lifeText_->SetText("Lives: "+ std::to_string(GetContext().player_->GetLives()), false);
    moneyText_->SetText("Money: " + std::to_string(GetContext().player_->GetPlayerMoney()), false);
    GUIContainer_.Update(dt);
    sidebarWorld_.Update(dt);
    //backgroundShape_.setPosition(GUIContainer_.getPosition());
}

void SidebarState::AddTowerButton(Tower::Type type, float relX, float relY, sf::IntRect normalTexture, sf::IntRect selectedTexture, const FontHolder& fonts)
{
        //std::cout << "we got hereeeeeeeeeee" << std::endl;

        auto towerButton = std::make_shared<GUI::TowerButton>(type, towerPosition_, *GetContext().fonts_, *GetContext().textures_, normalTexture, selectedTexture);
        sf::Vector2f relativePosition(relX, relY);
        towerButton->setOrigin(towerButton->GetGlobalBounds().width/2.f, towerButton->GetGlobalBounds().height/2.f);
        towerButton->setPosition(towerPosition_ + relativePosition);
        std::unique_ptr<TowerPicture> towerPic(new TowerPicture(type, *GetContext().textures_, towerPosition_ + relativePosition));
       // std::cout << "we got hereeeeeeeeeee2" << std::endl;

        towerButton->AddTowerPicture(towerPic.get());
        //towerButton->GetTowerPic()
        //sf::Vector2f buttonPosition = towerButton->GetWorldPosition();
        sidebarWorld_.AddTowerPicture(std::move(towerPic));
        
        //towerButton->SetText(towerName.append("\n").append(std::to_string(towerTable[type].price)));
        GUIContainer_.Pack(towerButton, true); //Pack it before getting position to get the real pos
        
        towerButton->SetCallback([this, towerButton] ()
            {
                if (GetContext().player_->BuyTower(towerTable[towerButton->GetTowerType()].price))
                {
                    Command command;
                    command.category_ = Category::Type::GameField;
                    command.gameFieldAction_ = GameFieldAction(
                                [towerButton] (GameField& gameField, sf::Time)
                                {
                                    //std::cout << "Button pressed!" <<std::endl;
                                    
                                    gameField.AddTower(towerButton->GetTowerType(), towerButton->GetClickPosition());
                                    // cannot buy tower if does not have enough money
                                }
                    );

                    GUIController_.SendCommand(command);
                    towerButton->GetTowerPic()->Activate();
                    
                } else
                {
                    showInfotext_ = true;
                    
                    std::cout << "not enough money to buy towers!" << std::endl;
                }

            });

        auto towerText = std::make_shared<GUI::Label>(towerTable[type].name, fonts, 20, Fonts::Main);
        towerText->setOrigin(towerText->GetGlobalBounds().width/2.f, towerText->GetGlobalBounds().height/2.f);
        towerText->setPosition(towerButton->GetWorldPosition().x + towerButton->GetGlobalBounds().width/2.f, towerButton->GetWorldPosition().y + towerButton->GetGlobalBounds().height + 10.f);
        towerText->SetColor(sf::Color(236,212,182));

        auto priceText = std::make_shared<GUI::Label>("Price: " + std::to_string(towerTable[type].price), fonts, 20, Fonts::Main);
        priceText->setOrigin(priceText->GetGlobalBounds().width/2.f, priceText->GetGlobalBounds().height/2.f);
        priceText->setPosition(towerButton->GetWorldPosition().x + towerButton->GetGlobalBounds().width/2.f, towerButton->GetWorldPosition().y + towerButton->GetGlobalBounds().height + 30.f);
        priceText->SetColor(sf::Color(236,212,182));

        towerTexts_.push_back(towerText);
        towerTexts_.push_back(priceText);
}

bool SidebarState::HandleEvent(const sf::Event& event) {
    //std::cout << "Sidebar state handleevent" << std::endl;
	GUIContainer_.HandleEvent(event);
    GetContext().player_->HandleEvent(event, sidebarWorld_.GetCommandQueue());
    //std::cout << "player handled events" << std::endl;

    //GUIController_.HandleEvent(event, sidebarWorld_.GetCommandQueue());


	    // Make the mouse-related events available for all
    if ((event.type == sf::Event::MouseMoved) || (event.type == sf::Event::MouseButtonPressed) || (event.type == sf::Event::MouseButtonReleased))
    {

        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (GetContext().player_->InfoRequested())
            {
                std::cout << "Sidebar now recognised that player is requesting info" << std::endl;
                RequestStackPop(); // Should pop this state 
                RequestStackPush(States::ID::TowerInfo); // Pushes the upgrade/sell side bar
                GetContext().player_->ResetInfoRequestStatus(); // Resets the player to not request info
                
            }
            //player_.ResetInfoRequestStatus();
            //player_.ResetInfoPopStatus();
        
        }
        return true;
    }

    if (event.type == sf::Event::KeyReleased)
    {
        return false;
    }
        
    // If I is pressed, make the sidebar go away
	if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::I))
    {
       // std::cout << "S: I-KeyPressed" << std::endl;
		RequestStackPop();
    }
        // If I is pressed, make the sidebar go away
	/*if (sf::Event::KeyPressed && event.key.code == sf::Keyboard::U)
    {
       // std::cout << "Sidebar: U-KeyPressed" << std::endl;
		RequestStackPop();
        RequestStackPush(States::ID::Sidebar);
        RequestStackPush(States::ID::TowerInfo);
    }*/
    
    //If p is pressed, go to Pause state
    if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::P))
    {
		RequestStackPush(States::ID::Pause);
	}
    if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::S))
    {
        return true;
    }

    //Otherwise, don't propagate the events
    return false;
}