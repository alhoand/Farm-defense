#include "game_over_state.hpp"
#include "../button.hpp"
#include "../player.hpp"

#include <cmath>
#include <string>


GameOverState::GameOverState(StateStack& stack, Context context)
    : State(stack, context),
    gameOverText_(),
    GUIContainer_(),
    elapsedTime_(sf::Time::Zero),
    typedText_("Type player name: "),
    text_(),
    name_(""),
    player_(*context.player_)
    {
        sf::Font& font = context.fonts_->Get(Fonts::Main);
        sf::Vector2f viewSize = context.window_->getView().getSize();

/*         text_.setString("");
        text_.setFont(font);
        //text_.setColor(sf::Color::Red);
        text_.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y); */

        gameOverText_.setFont(font);
        if (context.player_->GetGameStatus() == Player::GameStatus::GameWon)
        {
            gameOverText_.setString("You won the game and defeated all enemies!\nWhat do you want to do next?"); //\nYour score is: " + std::to_string(context.player_->GetPlayerMoney())
        } else if (context.player_->GetGameStatus() == Player::GameStatus::GameLost)
        {
            gameOverText_.setString("You lost the game :(\nWhat do you want to do next?");
        }
        context.player_->SetGameStatus(Player::GameRunning);
        gameOverText_.setCharacterSize(50);
        sf::FloatRect bounds = gameOverText_.getLocalBounds();
        gameOverText_.setOrigin(::floor(bounds.left + bounds.width / 2.f), std::floor(50 + bounds.top + bounds.height / 2.f));
        gameOverText_.setPosition(0.5f * viewSize.x, 0.3f * viewSize.y);

        auto menuButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_, sf::IntRect(0,104,100,88),sf::IntRect(0,192,100,88));
        menuButton->setPosition(550, 300);
        menuButton->SetText("Return to main menu");
        menuButton->SetCallback([this] ()
        {
            RequestStateClear();
            RequestStackPush(States::ID::Menu);
        });
        GUIContainer_.Pack(menuButton); 

        auto quitButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_, sf::IntRect(0,104,200,88),sf::IntRect(0,192,200,88));
        quitButton->setPosition(550, 400);
        quitButton->SetText("Ragequit");
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

    //window.clear();
    window.draw(backgroundShape);
    window.draw(gameOverText_);
    window.draw(GUIContainer_);

    //window.draw(text_);
    //window.display();

}

bool GameOverState::Update(sf::Time)
{
/*     elapsedTime_ += dt;

   // while (elapsedTime_ >= sf::seconds(.5f))
    {
        elapsedTime_ -= sf::seconds(.5f);
        if (typedText_.getSize() > 0)
        {
            text_.setString(text_.getString() + typedText_[0]);
            name_ += typedText_[0];
            typedText_ = typedText_.toAnsiString().substr(1);
        }
    } */
    return false;
}

bool GameOverState::HandleEvent(const sf::Event& event)
{ 
/*     if (event.type == sf::Event::TextEntered)
    {
        typedText_ += event.text.unicode;
    } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
    {
        player_.SetPlayerName(name_ );
        std::cout << "Player name:" << player_.GetPlayerName().toAnsiString() << std::endl;
    } */

    GUIContainer_.HandleEvent(event);
    return false; 
}