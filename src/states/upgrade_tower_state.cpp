#include "../resource_holder.hpp"
#include "../button.hpp"
#include "../label.hpp"
#include "../towers/tower.hpp"
#include <cmath>
#include "upgrade_tower_state.hpp"
#include <memory>
#include <string>
#include <iostream>
#include "../utility.hpp"
#include <cassert>

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
        titleText_->setPosition(viewSize_.x/2.f, 370.f);
        GUIContainer_.Pack(titleText_, true);

        descriptionText_ = std::make_shared<GUI::Label>("", *context.fonts_, 30, Fonts::Main);
        descriptionText_->CenterTextOrigin();
        descriptionText_->setPosition(viewSize_.x/2.f, 420.f);
        GUIContainer_.Pack(descriptionText_, true);
        
        auto upgradeButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_,sf::IntRect(0,104,200,88),sf::IntRect(0,192,200,88));
        upgradeButton->setOrigin(upgradeButton->GetGlobalBounds().width/2.f, upgradeButton->GetGlobalBounds().height/2.f);
        upgradeButton->setPosition(viewSize_.x/2.f, 500.f);
        upgradeButton->SetText("Upgrade");
        upgradeButton->SetCallback([this] ()
        {
            GUI::Component::Ptr temp = GetContext().GUIContainer_->GetChild(GUI::ID::ActiveSceneNode);
            auto activeTowerComponent = std::dynamic_pointer_cast<GUI::SceneNodeComponent>(temp);
            assert(activeTowerComponent);
            if (activeTowerComponent) 
            {
                if (Tower* tower = dynamic_cast<Tower*>(activeTowerComponent->GetNode()))
                {
                    std::cout << "Tower count: " << tower->TowerCount() << std::endl;
                }else
                {
                    //activeTowerComponent->GetNode()->rotate(45.f);
                }
                
            }
	    });
        GUIContainer_.Pack(upgradeButton, true);
        GUI::Component::Ptr temp = GetContext().GUIContainer_->GetChild(GUI::ID::ActiveSceneNode);
        auto activeTowerComponent = std::dynamic_pointer_cast<GUI::SceneNodeComponent>(temp);
        GUIContainer_.Pack(activeTowerComponent);

        backgroundShape_.setFillColor(sf::Color(160,82,45,0));
        backgroundShape_.setSize(viewSize_);
        GUIContainer_.setPosition(context.window_->getView().getSize().x - viewSize_.x, 0);
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

    auto GUINode = GetActiveNode(GUI::ID::ActiveSceneNode);
    
    if (Tower* towerNode = dynamic_cast<Tower*>(GUINode))
    {
        //std::cout << "succesful towernode found" << std::endl;

        titleText_->SetText("Tower");
        descriptionText_->SetText("HP: " + std::to_string(towerNode->GetHitpoints()));
    }else
    {
    //    std::cout << "U: No tower node found" << std::endl;

    }
    
    GUIContainer_.Update(dt);
    backgroundShape_.setPosition(GUIContainer_.getPosition());
}   


bool UpgradeTowerState::HandleEvent(const sf::Event& event) {
	GUIContainer_.HandleEvent(event);

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
	if (sf::Event::KeyPressed && event.key.code == sf::Keyboard::U)
    {
        std::cout << "KeyPressed" << std::endl;
		RequestStackPop();
        RequestStackPop();
    }
    //If p is pressed, go to Pause state
    if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P))
    {
		RequestStackPush(States::ID::Pause);
	}
    if (sf::Event::KeyPressed && event.key.code == sf::Keyboard::I)
    {
        std::cout << "Upgrade: I-KeyPressed" << std::endl;
		RequestStackPop();
        //RequestStackPush(States::ID::Sidebar);
    }

    //Otherwise, don't propagate the events
    return false;
}

//Helper function
SceneNode* UpgradeTowerState::GetActiveNode(GUI::ID type) const {
    auto GUIComponent = GetContext().GUIContainer_->GetChild(GUI::ID::ActiveSceneNode);
    auto GUINodeComponent = std::dynamic_pointer_cast<GUI::SceneNodeComponent>(GUIComponent);
    return GUINodeComponent->GetNode();
}
