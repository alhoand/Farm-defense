#include "score_state.hpp"
#include "../button.hpp"
#include "../resource_holder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


#include <iostream>

// for makinf high score list
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

#include <SFML/Graphics/Rect.hpp> 



ScoreState::ScoreState(StateStack& stack, Context context)
: State(stack, context)
, GUIContainer_(context)
, textList_()
{
    sf::Font& font = context.fonts_->Get(Fonts::Main);

	sf::Texture& texture = context.textures_->Get(Textures::ID::TitleBackground);
	backgroundSprite_.setTexture(texture);

	auto menuButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
    menuButton->setPosition(1200, 20);
    menuButton->SetText("Return to main menu");
    menuButton->SetCallback([this] ()
    {
        RequestStateClear();
        RequestStackPush(States::ID::Menu);
    });
    GUIContainer_.Pack(menuButton); 

    // read high scores from file
    std::ifstream file;
    file.open("/u/38/mikkonj8/unix/Documents/cpp_project/tower-defense-2020-2/src/states/highscores.txt");

    std::string line;
    sf::Text text("", font, 30);
    textList_.push_back(sf::Text("High scores", font, 50));
    
    if(file.is_open())
    {
        int i = 1;
        std::cout << "file is open" << std::endl;
        while(std::getline(file, line))
        {
            std::cout << "loading a line from file: " << line << std::endl;
            //Getting every line of the .txt file and putting it in the 'line' string
            text.setString(std::to_string(i++) + ". " + line);
            textList_.push_back(text);

        }
        file.close();
    }
    else
    {
        std::cout << "could not open the file" << std::endl;
    }

}

void ScoreState::Draw()
{
	sf::RenderWindow& window = *GetContext().window_;

	window.setView(window.getDefaultView());

	window.draw(backgroundSprite_);

    sf::RectangleShape backgroundShape;
    
    sf::FloatRect bounds = backgroundShape.getLocalBounds();
    backgroundShape.setFillColor(sf::Color(10, 50, 20, 150));
    backgroundShape.setSize(sf::Vector2f(window.getSize()));
    //backgroundShape.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(50 + bounds.top + bounds.height / 2.f));
    //backgroundShape.setScale(0.9, 0.9);

    window.draw(backgroundShape);

    float currentHeight = 25;
        for(auto it = textList_.begin(); it != textList_.end(); it++)
        {
            sf::Text& text = *it;
            sf::FloatRect bounds = text.getLocalBounds();
            text.setPosition(50.f, (currentHeight));
            ;

            if (it == textList_.begin())
            {
                currentHeight += bounds.height + 25;
            } else
            {
                currentHeight += bounds.height + 10;
            }

            window.draw(text);
        }
    window.draw(GUIContainer_);
}

bool ScoreState::Update(sf::Time)
{
	return true;
}

bool ScoreState::HandleEvent(const sf::Event& event)
{
	GUIContainer_.HandleEvent(event);
	return false;
}



/* 
{
        

        float i = 0;
        for(std::list<sf::Text>::iterator it = textList.begin(); it != textList.end(); ++it)
        {
                sf::Text& text = *it;
                sf::FloatRect boundings = text.getLocalBounds();
                text.setPosition(0.f, i * (boundings.height + 5));
                ++i;

                //draw or something here
        }
} */