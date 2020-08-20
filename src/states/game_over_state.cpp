#include "game_over_state.hpp"
#include "../button.hpp"
#include "../data_tables.hpp"
#include "../player.hpp"

namespace {
	const std::vector<GUIData> table = InitializeGUIData();
}

GameOverState::GameOverState(StateStack& stack, Context context)
    : State(stack, context),
    gameOverText_(),
    GUIContainer_(context)
    {
        sf::Font& font = context.fonts_->Get(Fonts::Main);
        sf::Vector2f viewSize = context.window_->getView().getSize();

        gameOverText_.setFont(font);
        if (context.player_->GetGameStatus() == Player::GameStatus::GameWon)
        {
            gameOverText_.setString("You won the game and defeated all enemies!\nWhat do you want to do next?");
        } else if (context.player_->GetGameStatus() == Player::GameStatus::GameLost)
        {
            gameOverText_.setString("You lost the game :(\nWhat do you want to do next?");
        }
        gameOverText_.setCharacterSize(70);
        sf::FloatRect bounds = gameOverText_.getLocalBounds();
        gameOverText_.setOrigin(::floor(bounds.left + bounds.width / 2.f), std::floor(50 + bounds.top + bounds.height / 2.f));
        gameOverText_.setPosition(0.5f * viewSize.x, 0.3f * viewSize.y);

        auto menuButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
        menuButton->setPosition(550, 300);
        menuButton->SetText("Return to main menu");
        menuButton->SetCallback([this] ()
        {
            RequestStateClear();
            RequestStackPush(States::ID::Menu);
        });
        GUIContainer_.Pack(menuButton); 

        auto quitButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
        quitButton->setPosition(550, 400);
        quitButton->SetText("Quit game");
        quitButton->SetCallback([this] ()
        {
            RequestStateClear();
        });
        GUIContainer_.Pack(quitButton);  

        //Can we do retry button?????
    }

void GameOverState::Draw()
{
    sf::RenderWindow& window = *GetContext().window_;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(sf::Vector2f(window.getSize()));

    window.draw(backgroundShape);
    window.draw(gameOverText_);
    window.draw(GUIContainer_);
}

bool GameOverState::Update(sf::Time)
{
    return false;
}

bool GameOverState::HandleEvent(const sf::Event& event)
{
    GUIContainer_.HandleEvent(event);
    return false;
}