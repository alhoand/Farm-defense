#include "../resource_holder.hpp"
#include "../button.hpp"
#include "../label.hpp"
#include "../tower.hpp"
#include <cmath>
#include "upgrade_tower_state.hpp"
#include <memory>
#include <string>
#include <iostream>
#include "../utility.hpp"

UpgradeTowerState::UpgradeTowerState(StateStack& stack, Context context) :
    State(stack, context),
    backgroundSprite_(),
    backgroundShape_(),
    titleText_(nullptr),
    descriptionText_(nullptr),
    viewSize_(context.window_->getView().getSize().x/4.f, context.window_->getView().getSize().y),
    GUIContainer_()
    {
        titleText_ = std::make_shared<GUI::Label>("", *context.fonts_, 40, Fonts::Main);
        titleText_->CenterTextOrigin();
        titleText_->setPosition(viewSize_.x/2.f, 30.f);
        GUIContainer_.Pack(titleText_, true);

        descriptionText_ = std::make_shared<GUI::Label>("", *context.fonts_, 30, Fonts::Main);
        descriptionText_->CenterTextOrigin();
        descriptionText_->setPosition(viewSize_.x/2.f, 150.f);
        GUIContainer_.Pack(descriptionText_, true);
        
        auto upgradeButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
        upgradeButton->setOrigin(upgradeButton->GetGlobalBounds().width/2.f, upgradeButton->GetGlobalBounds().height/2.f);
        upgradeButton->setPosition(viewSize_.x/2.f, 300.f);
        upgradeButton->SetText("Upgrade");
        upgradeButton->SetCallback([this] ()
        {
            GUI::Component::Ptr temp = GetContext().GUIContainer_->GetChild(GUI::ID::ActiveSceneNode);
           // std::cout << "Use count for activenode comp in button" << temp.use_count()<< std::endl;
            auto activeTowerComponent = std::dynamic_pointer_cast<GUI::SceneNodeComponent>(temp);
            //std::cout << "Use count for activetower comp in button" << activeTowerComponent.use_count()<< std::endl;

            if (activeTowerComponent) {
                 
                //activeTowerComponent->GetNode()->rotate(45.f);
                if (Tower* tower = dynamic_cast<Tower*>(activeTowerComponent->GetNode()))
                {
                    std::cout << "Tower count: " << tower->TowerCount() << std::endl;
                    std::cout << "Pöö" << std::endl;
                }else
                {
                    //activeTowerComponent->GetNode()->rotate(45.f);
                }
                
            }else{
                std::cout << "There was not an active tower" << std::endl;
            }
            std::cout << "Tower upgrade button was pressed." << std::endl;
	    });
        std::cout << "Constructor of upgrade tower state" << std::endl;
        GUIContainer_.Pack(upgradeButton, true);
        GUI::Component::Ptr temp = GetContext().GUIContainer_->GetChild(GUI::ID::ActiveSceneNode);
       //std::cout << "Use count for activenode comp in constructor " << temp.use_count()<< std::endl;
       // std::cout << "There was a guicontainer in the context" << std::endl;
        auto activeTowerComponent = std::dynamic_pointer_cast<GUI::SceneNodeComponent>(temp);
       // std::cout << "There was a dynamic cast done to the component" << std::endl;
        //std::cout << "Use count for activenode comp in constructor before packing" << temp.use_count()<< std::endl;
        //std::cout << "Use count for activetower comp in constructor before packing" << activeTowerComponent.use_count()<< std::endl;

        GUIContainer_.Pack(activeTowerComponent);
        //std::cout << "Use count for activenode comp in constructor after packing" << temp.use_count()<< std::endl;
        //std::cout << "Use count for activetower comp in constructor after packing" << activeTowerComponent.use_count()<< std::endl;


        backgroundShape_.setFillColor(sf::Color(0, 0, 0, 128));
        backgroundShape_.setSize(viewSize_);
        GUIContainer_.setPosition(context.window_->getView().getSize().x - viewSize_.x, 0);
       // std::cout << "End of upgradetower constructor" << std::endl;
    }

void UpgradeTowerState::Draw() {
    sf::RenderWindow& window = *GetContext().window_;
    window.setView(window.getDefaultView());

    window.draw(backgroundShape_);
    window.draw(GUIContainer_);
}

bool UpgradeTowerState::Update(sf::Time dt) {
    UpdateGUI(dt);
	return true;
}

void UpgradeTowerState::UpdateGUI(sf::Time dt) {
    auto GUIComponent = GetContext().GUIContainer_->GetChild(GUI::ID::ActiveSceneNode);
   // std::cout << "Upgrade: A guicomponent was fetched" <<std::endl;
    if (GUIComponent->GetType() == GUI::ID::ActiveSceneNode){
        //std::cout << "Jiihaa!" << std::endl;
    }
    auto GUINodeComponent = std::dynamic_pointer_cast<GUI::SceneNodeComponent>(GUIComponent);
    auto GUINode = GUINodeComponent->GetNode();
  //std::cout << GUINodeComponent->IsActive() << std::endl;
    
   // std::cout << "U: a dynamic pointer cast was made" << std::endl;
    if (GUINode) {
        //std::cout << "U: Node pos: " << GUINode->getPosition().x << std::endl;
    }
    if (Tower* towerNode = dynamic_cast<Tower*>(GUINode))
    {
        //std::cout << "succesful towernode found" << std::endl;

        titleText_->SetText("Tower");
        descriptionText_->SetText("HP: " + std::to_string(towerNode->GetHitpoints()));
    //    std::cout << "U: end of setting texts" << std::endl;
    }else
    {
    //    std::cout << "U: No tower node found" << std::endl;

    }
    
    GUIContainer_.Update(dt);
  //  std::cout << "U: container update made" << std::endl;
    backgroundShape_.setPosition(GUIContainer_.getPosition());
    //std::cout << "container pos: (" << GUIContainer_.GetWorldPosition().x << ", " << GUIContainer_.GetWorldPosition().y << ")" << std::endl;
 //   std::cout << "U: end of update" << std::endl;
}   


bool UpgradeTowerState::HandleEvent(const sf::Event& event) {
	
	GUIContainer_.HandleEvent(event);
	
    if (event.type == sf::Event::KeyReleased)
    {
        std::cout << "Event was keyreleased" <<std::endl;
        return false;
    }
        

    // If I is pressed, return to the game
	if (sf::Event::KeyPressed && event.key.code == sf::Keyboard::I)
    {
		// I pressed, remove itself to return to the game
		RequestStackPop();
    }
    if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P))
    {
		RequestStackPush(States::ID::Pause);
	}

    //Make the mouse events available for game state
    if ((event.type == sf::Event::MouseMoved) || (event.type == sf::Event::MouseButtonPressed))
    {
        return true;
    }


    return false;
}