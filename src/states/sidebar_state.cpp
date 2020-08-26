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
    , descriptionText_(nullptr)
    , viewSize_(context.window_->getView().getSize().x/4.f, context.window_->getView().getSize().y)
    , GUIContainer_() 
    , GUIController_(*context.GUIController_)
    , towerPosition_(sf::Vector2f(viewSize_.x/2.f, 230.f))
    , sidebarWorld_(*context.window_,towerPosition_)
    , currentWave_(0)
    {
        GUIContainer_.setPosition(context.window_->getView().getSize().x - viewSize_.x, 0);
        sidebarWorld_.SetGraphPosition(GUIContainer_.getTransform());
        std::cout << "Here we are!" << std::endl;
        
        titleText_ = std::make_shared<GUI::Label>("Wave 0", *context.fonts_, 35, Fonts::Main);
        //titleText_->CenterTextOrigin();
        titleText_->setPosition(50.f, 10.f);
        //GUIContainer_.Pack(titleText_, true);
        std::cout << "Here we are 2!" << std::endl;

        auto waveButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_, sf::IntRect(0,104,200,88),sf::IntRect(0,192,200,88));
        waveButton->setOrigin(waveButton->GetGlobalBounds().width/2.f, waveButton->GetGlobalBounds().height/2.f);
        waveButton->setPosition(viewSize_.x/2.f, 100.f);
        waveButton->SetText("Next wave");
        waveButton->SetCallback([this, waveButton] ()
            {
                std::cout << "Wave button was pressed." << std::endl;
                Command waveCommand;
                waveCommand.category_ = Category::Type::GameField;
                waveCommand.gameFieldAction_ = GameFieldAction(
                    [this, waveButton] (GameField& gameField, sf::Time dt)
                    {
                        if (gameField.CanSpawnNewWave())
                        {
                            gameField.NextEnemyWave();
                            titleText_->SetText("Wave " + std::to_string(++currentWave_), false);
                        } 
                    }
                );
                GUIController_.SendCommand(waveCommand);
               
            });
        GUIContainer_.Pack(waveButton, true);

        AddTowerButton(Tower::Type::Basic, -100.f, 0.f, sf::IntRect(0,104,200,88),sf::IntRect(0,192,200,88));
        AddTowerButton(Tower::Type::Slowing, +100.f, 0.f, sf::IntRect(0,104,200,88),sf::IntRect(0,192,200,88));
        AddTowerButton(Tower::Type::Bombing, -100.f, 230.f, sf::IntRect(0,104,200,88),sf::IntRect(0,192,200,88));
        AddTowerButton(Tower::Type::Super, +100.f, 230.f, sf::IntRect(0,104,200,88),sf::IntRect(0,192,200,88));

        backgroundShape_.setFillColor(sf::Color(160,82,45,235));
        backgroundShape_.setSize(viewSize_);
        std::cout << "end of sidebar constructor" << std::endl;
    }

void SidebarState::Draw() {
    sf::RenderWindow& window = *GetContext().window_;
    window.setView(window.getDefaultView());

    window.draw(backgroundShape_);
    window.draw(*titleText_);
    window.draw(GUIContainer_);
    sidebarWorld_.Draw();
}

bool SidebarState::Update(sf::Time dt) {
    UpdateGUI(dt);
	return true;
}

void SidebarState::UpdateGUI(sf::Time dt) {
    GUIContainer_.Update(dt);
    sidebarWorld_.Update(dt);
    backgroundShape_.setPosition(GUIContainer_.getPosition());
}

void SidebarState::AddTowerButton(Tower::Type type, float relX, float relY, sf::IntRect normalTexture, sf::IntRect selectedTexture)
{
        std::cout << "we got hereeeeeeeeeee" << std::endl;

        auto towerButton = std::make_shared<GUI::TowerButton>(type, towerPosition_, *GetContext().fonts_, *GetContext().textures_, normalTexture, selectedTexture);
        sf::Vector2f relativePosition(relX, relY);
        towerButton->setOrigin(towerButton->GetGlobalBounds().width/2.f, towerButton->GetGlobalBounds().height/2.f);
        towerButton->setPosition(towerPosition_ + relativePosition);
        std::unique_ptr<TowerPicture> towerPic(new TowerPicture(type, *GetContext().textures_, towerPosition_ + relativePosition));
        std::cout << "we got hereeeeeeeeeee2" << std::endl;

        towerButton->AddTowerPicture(towerPic.get());
        //sf::Vector2f buttonPosition = towerButton->GetWorldPosition();
        sidebarWorld_.AddTowerPicture(std::move(towerPic));
        
        std::string towerName = towerTable[type].name;
        towerButton->SetText(towerName.append("\n").append(std::to_string(towerTable[type].price)));
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
                } else
                {
                    std::cout << "not enough money to buy towers!" << std::endl;
                }

            });
}

bool SidebarState::HandleEvent(const sf::Event& event) {
	GUIContainer_.HandleEvent(event);
    GetContext().player_->HandleEvent(event, sidebarWorld_.GetCommandQueue());
    //GUIController_.HandleEvent(event, sidebarWorld_.GetCommandQueue());
	    // Make the mouse-related events available for all
    if ((event.type == sf::Event::MouseMoved) || (event.type == sf::Event::MouseButtonPressed))
    {
        return true;
    }

    if (event.type == sf::Event::KeyReleased)
    {
        return false;
    }
        
    // If I is pressed, make the sidebar go away
	if (sf::Event::KeyPressed && event.key.code == sf::Keyboard::I)
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
        RequestStackPush(States::ID::GameUpgradeTowerSideBar);
    }*/
    
    //If p is pressed, go to Pause state
    if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P))
    {
		RequestStackPush(States::ID::Pause);
	}

    //Otherwise, don't propagate the events
    return false;
}