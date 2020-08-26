

#include "menu_state.hpp"
#include "../button.hpp"
#include "../resource_holder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include <iostream>


MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, GUIContainer_()
{
	sf::Texture& texture = context.textures_->Get(Textures::ID::TitleBackground);
	backgroundSprite_.setTexture(texture);
	logoSprite_.setTexture(context.textures_->Get(Textures::ID::logo));
	logoSprite_.setPosition(120,50);
	auto playButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_,sf::IntRect(0,104,200,88),sf::IntRect(0,192,200,88));
	playButton->setPosition(100, 250);
	playButton->SetText("Play");
	playButton->SetCallback([this] ()
	{
		RequestStackPop();
		RequestStackPush(States::ID::Game);
		RequestStackPush(States::ID::Sidebar);
	});

	/* auto scoreButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_,sf::IntRect(200,104,200,88),sf::IntRect(200,192,200,88));
	scoreButton->setPosition(100, 350);
	scoreButton->SetText("High Scores");
	scoreButton->SetCallback([this] ()
	{
		RequestStackPop();
		RequestStackPush(States::ID::Score);
	}); */
/*
	auto settingsButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
	settingsButton->setPosition(100, 300);
	settingsButton->SetText("Settings");
	settingsButton->SetCallback([this] ()
	{
		RequestStackPush(States::ID::Settings);
	});*/
	auto exitButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_,sf::IntRect(0,104,200,88),sf::IntRect(0,192,200,88));
	exitButton->setPosition(100, 350);
	exitButton->SetText("Exit");
	exitButton->SetCallback([this] ()
	{
		RequestStackPop();
	});

	//GUIContainer_.Pack(scoreButton);
	GUIContainer_.Pack(playButton);
	//GUIContainer_.Pack(settingsButton);
	GUIContainer_.Pack(exitButton);
}

void MenuState::Draw()
{
	sf::RenderWindow& window = *GetContext().window_;

	window.setView(window.getDefaultView());

	window.draw(backgroundSprite_);
	window.draw(logoSprite_);
	window.draw(GUIContainer_);
}

bool MenuState::Update(sf::Time)
{
	return true;
}

bool MenuState::HandleEvent(const sf::Event& event)
{
	GUIContainer_.HandleEvent(event);
	return false;
}