
#include "application.hpp"
#include "state.hpp"
#include "state_identifiers.hpp"
#include <SFML/System/Time.hpp>
#include "title_state.hpp"
#include "game_state.hpp"
#include <iostream>

static const sf::Time timePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
    : window_(sf::VideoMode(1024,768), "Tower Defense", sf::Style::Close),
    viewOffset_(sf::Vector2f(0.f, 0.f)),
    textures_(),
    fonts_(),
    player_(window_, viewOffset_),
    stateStack_(State::Context(window_, textures_, fonts_, player_, viewOffset_))
    { 
        fonts_.Load(Fonts::ID::Title, "../media/fonts/Lato-Regular.ttf");
        textures_.Load(Textures::ID::TitleBackground, "../media/textures/otaniemi.jpg");
        RegisterStates();
        stateStack_.PushState(States::ID::Title);
    }
    

void Application::RegisterStates() {
    stateStack_.RegisterState<TitleState>(States::ID::Title);
    //stateStack_.RegisterState<MenuState>(States::ID::Menu);
    stateStack_.RegisterState<GameState>(States::ID::Game);
}

void Application::Run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    
    while (window_.isOpen()) {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        //ProcessInput();
        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            ProcessInput();
            Update(timePerFrame);

            if(stateStack_.IsEmpty()) {
                window_.close();
            }
        }
        Render();
    }
}

void Application::ProcessInput() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        stateStack_.HandleEvent(event);

        if (event.type == sf::Event::Closed)
			window_.close();
    }
}

void Application::Update(sf::Time dt) {
    //std::cout << "The state stack was updated" << std::endl;
    stateStack_.Update(dt);
}

void Application::Render() {
    window_.clear();
    stateStack_.Draw();
    
    window_.setView(window_.getDefaultView()); // not necessary right now 
    window_.display();
    
}