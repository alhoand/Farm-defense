#include "end_of_level_state.hpp"
#include "../command_queue.hpp"
#include "../game_field.hpp"
#include "../button.hpp"
#include "../player.hpp"

#include <cmath>
#include <string>


EndOfLevelState::EndOfLevelState(StateStack& stack, Context context)
    : State(stack, context),
    levelOverText_(),
    GUIContainer_(),
    GUIController_(*context.GUIController_)
    {
        sf::Font& font = context.fonts_->Get(Fonts::Main);
        sf::Vector2f viewSize = context.window_->getView().getSize();

        levelOverText_.setFont(font);
        levelOverText_.setString("You completed the level!");
        levelOverText_.setCharacterSize(70);

        sf::FloatRect bounds = levelOverText_.getLocalBounds();
        levelOverText_.setOrigin(::floor(bounds.left + bounds.width / 2.f), std::floor(50 + bounds.top + bounds.height / 2.f));
        levelOverText_.setPosition(0.5f * viewSize.x, 0.3f * viewSize.y);

        auto continueButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_, sf::IntRect(0,104,200,88),sf::IntRect(0,192,200,88));
        continueButton->setPosition(550, 300);
        continueButton->SetText("Continue game");
        continueButton->SetCallback([this, continueButton] ()
        {
            std::cout << "continue pressed" << std::endl;
            Command nextLevelCommand;
            nextLevelCommand.category_ = Category::Type::GameField;
            nextLevelCommand.gameFieldAction_ = GameFieldAction(
                [this, continueButton] (GameField& gameField, sf::Time)
                {
                    gameField.NextLevel();
                }
            );
            GUIController_.SendCommand(nextLevelCommand);
            RequestStackPop();                
        });
        GUIContainer_.Pack(continueButton); 

        auto menuButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_, sf::IntRect(200,104,200,88),sf::IntRect(200,192,200,88));
        menuButton->setPosition(550, 400);
        menuButton->SetText("Return to main menu");
        menuButton->SetCallback([this] ()
        {
            RequestStateClear();
            RequestStackPush(States::ID::Menu);
        });
        GUIContainer_.Pack(menuButton); 

        auto quitButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_,  sf::IntRect(0,104,200,88),sf::IntRect(0,192,200,88));
        quitButton->setPosition(550, 500);
        quitButton->SetText("Ragequit");
        quitButton->SetCallback([this] ()
        {
            RequestStateClear();
        });
        GUIContainer_.Pack(quitButton);  
    }

void EndOfLevelState::Draw()
{
    sf::RenderWindow& window = *GetContext().window_;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(sf::Vector2f(window.getSize()));
    
    window.draw(backgroundShape);
    window.draw(levelOverText_);
    window.draw(GUIContainer_);

}

bool EndOfLevelState::Update(sf::Time)
{
    return false;
}

bool EndOfLevelState::HandleEvent(const sf::Event& event)
{
    GUIContainer_.HandleEvent(event);
    return false;
}