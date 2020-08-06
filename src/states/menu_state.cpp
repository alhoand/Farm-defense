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
	auto playButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
	playButton->setPosition(100, 250);
	playButton->SetText("Play");
	playButton->SetCallback([this] ()
	{
		RequestStackPop();
		RequestStackPush(States::ID::Game);
	});
/*
	auto settingsButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
	settingsButton->setPosition(100, 300);
	settingsButton->SetText("Settings");
	settingsButton->SetCallback([this] ()
	{
		RequestStackPush(States::ID::Settings);
	});*/
	auto exitButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
	exitButton->setPosition(100, 350);
	exitButton->SetText("Exit");
	exitButton->SetCallback([this] ()
	{
		RequestStackPop();
	});
	GUIContainer_.Pack(playButton);
	//GUIContainer_.Pack(settingsButton);
	GUIContainer_.Pack(exitButton);
}

void MenuState::Draw()
{
	sf::RenderWindow& window = *GetContext().window_;

	window.setView(window.getDefaultView());

	window.draw(backgroundSprite_);
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