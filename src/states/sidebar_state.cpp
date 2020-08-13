#include "sidebar_state.hpp"
#include <memory>

SidebarState::SidebarState(StateStack& stack, Context context)
    : State(stack, context)
    , backgroundSprite_()
    , backgroundShape_()
    , titleText_(nullptr)
    , descriptionText_(nullptr)
    , viewSize_(context.window_->getView().getSize().x/4.f, context.window_->getView().getSize().y)
    , GUIContainer_() 
    {
        titleText_ = std::make_shared<GUI::Label>("Wave 0", *context.fonts_, 50, Fonts::Main);
        titleText_->CenterTextOrigin();
        titleText_->setPosition(viewSize_.x/2.f, 50.f);
        GUIContainer_.Pack(titleText_, true);

        auto waveButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_, sf::IntRect(0,104,200,88),sf::IntRect(0,192,200,88));
        waveButton->setOrigin(waveButton->GetGlobalBounds().width/2.f, waveButton->GetGlobalBounds().height/2.f);
        waveButton->setPosition(viewSize_.x/2.f, 200.f);
        waveButton->SetText("Next wave");
        waveButton->SetCallback([this] ()
            {
                std::cout << "Wave button was pressed." << std::endl;
            });
        auto towerButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_, sf::IntRect(0,104,200,88),sf::IntRect(0,192,200,88));
        towerButton->setOrigin(towerButton->GetGlobalBounds().width/2.f, towerButton->GetGlobalBounds().height/2.f);
        towerButton->setPosition(viewSize_.x/2.f, 400.f);
        towerButton->SetText("Add tower");
        towerButton->SetCallback([this] ()
            {
                std::cout << "Add new tower-button was pressed." << std::endl;
            });
        GUIContainer_.Pack(waveButton, true);
        GUIContainer_.Pack(towerButton, true);

        backgroundShape_.setFillColor(sf::Color(160,82,45,235));
        backgroundShape_.setSize(viewSize_);
        GUIContainer_.setPosition(context.window_->getView().getSize().x - viewSize_.x, 0);

    }

void SidebarState::Draw() {
    sf::RenderWindow& window = *GetContext().window_;
    window.setView(window.getDefaultView());

    window.draw(backgroundShape_);
    window.draw(GUIContainer_);
}

bool SidebarState::Update(sf::Time dt) {
    UpdateGUI(dt);
	return true;
}

void SidebarState::UpdateGUI(sf::Time dt) {
    GUIContainer_.Update(dt);
    backgroundShape_.setPosition(GUIContainer_.getPosition());
}

bool SidebarState::HandleEvent(const sf::Event& event) {
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
	if (sf::Event::KeyPressed && event.key.code == sf::Keyboard::I)
    {
        std::cout << "S: I-KeyPressed" << std::endl;
		RequestStackPop();
    }
        // If I is pressed, make the sidebar go away
	if (sf::Event::KeyPressed && event.key.code == sf::Keyboard::U)
    {
        std::cout << "Sidebar: U-KeyPressed" << std::endl;
		//RequestStackPop();
        //RequestStackPush(States::ID::GameUpgradeTowerSideBar);
    }
    
    //If p is pressed, go to Pause state
    if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P))
    {
		RequestStackPush(States::ID::Pause);
	}

    //Otherwise, don't propagate the events
    return false;
}