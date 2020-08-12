#include "game_state.hpp"
#include "../node_component.hpp"
#include "../resource_identifiers.hpp"
#include <memory>

GameState::GameState(StateStack& stack, Context context) :
    State(stack, context),
    gameField_(*context.window_, context.viewOffset_),
    player_(*context.player_),
    GUIContainer_()
    { 
        auto pauseButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_, sf::IntRect(108,0,55,53),sf::IntRect(0,0,55,54));
        pauseButton->setPosition(10, 10);
        pauseButton->SetType(GUI::ID::PlayPause);
        pauseButton->SetCallback([this] ()
	{
		RequestStackPush(States::ID::Pause);
	});
    std::cout << "Game state constructor started" << std::endl;
        GUIContainer_.Pack(pauseButton);

        //GetContext().GUIContainer_->Pack(pauseButton);
        //std::cout << "Guicontainer was in context" << std::endl;
        auto nodeComponent = std::make_shared<GUI::SceneNodeComponent>(nullptr);
        nodeComponent->SetType(GUI::ID::ActiveSceneNode);

        GUIContainer_.Pack(nodeComponent);
        GetContext().GUIContainer_->Pack(nodeComponent);
    
    }

void GameState::Draw() {
    gameField_.Draw(); // calls the gamefield to draw everything
    sf::RenderWindow& window = *GetContext().window_;
    window.draw(GUIContainer_);
}

bool GameState::Update(sf::Time dt) {
    gameField_.Update(dt); // updates the gamefield on each tick   
    UpdateGUI(); // TODO: make this call only when needed
    CommandQueue& commands = gameField_.GetCommandQueue();
	player_.HandleRealtimeInput(commands);

	return true;
}

bool GameState::HandleEvent(const sf::Event& event) {
    CommandQueue& commands = gameField_.GetCommandQueue();
    player_.HandleEvent(event, commands);

    if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P))
		RequestStackPush(States::ID::Pause);

    if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I)) {
        std::cout << "Requested info " << std::endl;
		RequestStackPush(States::ID::GameUpgradeTowerSideBar);
    }
        
    GUIContainer_.HandleEvent(event);
    return true;
}

void GameState::UpdateGUI() {
   //std::cout << "UpdateGUI in game state" << std::endl;

    std::pair<SceneNode*, bool> activeNode = gameField_.GetActiveNode();
    if (!activeNode.second && !activeNode.first) 
    {
        return;
    } //TODO: implement tower addition
        //GetContext().GUIComponent_->SetNode(nullptr);
    //std::cout << "UpdateGUI in game state" << std::endl;
    auto GUIComponent = GUIContainer_.GetChild(GUI::ID::ActiveSceneNode);
    
    if (Tower* activeTower = dynamic_cast<Tower*>(activeNode.first)) { // There is an active tower
        //std::cout << "There was an active tower in GUI!" << std::endl;
        auto GUINodeComponent = std::dynamic_pointer_cast<GUI::SceneNodeComponent>(GUIComponent);
        //std::cout << "GUiNodecomponent was got" << std::endl;
      //std::cout << activeTower->getPosition().x << ", " <<activeTower->getPosition().y  << std::endl;
        if (GUINodeComponent.get() != nullptr)
        {
            // std::cout << "The GUINode was fetched" << std::endl;
            if (auto GUINode = GUINodeComponent->GetNode()) // If there is a scene node pointer in the GUI
            {
                //std::cout << "There was a GUINode" << std::endl;
                if (Tower *GUITower = dynamic_cast<Tower*>(GUINode))
                {
                    if (GUITower == activeTower) 
                    { // If there is the same tower in GUI that is active, do nothing
                   // std::cout << "Sama tower!!! " << std::endl;
                        return;
                    }
                }
                
            }else
            {
                //std::cout << "There was no node in the guicomponent" << std::endl;

            }
        }
    
       // std::cout << "There was not a GUINode" << std::endl;
        
        //GetContext().GUIContainer_->SetNode(activeTower);
        //std::cout << "Pöö" << std::endl;
        auto NodeComponent = std::dynamic_pointer_cast<GUI::SceneNodeComponent>(GetContext().GUIContainer_->GetChild(GUI::ID::ActiveSceneNode));
       // std::cout << "Pöö2" << std::endl;
        NodeComponent->SetNode(activeTower);
       // if (Tower* tower = dynamic_cast<Tower*>(test->GetNode())) {
        //    std::cout << "Juhuu! in game state" <<std::endl;
       // }
        
       // std::cout << "The guinodecomponent's active node was set" << std::endl;
        //RequestStackPush(States::ID::GameUpgradeTowerSideBar);
    }
}

