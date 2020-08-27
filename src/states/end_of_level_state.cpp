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
    elapsedTime_(sf::Time::Zero)
    {
        sf::Font& font = context.fonts_->Get(Fonts::Main);
        sf::Vector2f viewSize = context.window_->getView().getSize();

        levelOverText_.setFont(font);

        levelOverText_.setString("You completed level " + std::to_string(context.player_->GetCurrentLevel()-1) + "!");
        levelOverText_.setCharacterSize(50);

        sf::FloatRect bounds = levelOverText_.getLocalBounds();
        levelOverText_.setOrigin(::floor(bounds.left + bounds.width / 2.f), std::floor(50 + bounds.top + bounds.height / 2.f));
        levelOverText_.setPosition(0.5f * viewSize.x, 0.3f * viewSize.y);

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
}

bool EndOfLevelState::Update(sf::Time dt)
{ 
    elapsedTime_ += dt;

    if (elapsedTime_ > sf::seconds(2))
    {
        RequestStackPop();
    }
    return false;
}

bool EndOfLevelState::HandleEvent(const sf::Event&)
{
    return false;
}