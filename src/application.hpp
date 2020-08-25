#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "resource_holder.hpp"
#include "resource_identifiers.hpp"
#include "state_identifiers.hpp"
#include "state_stack.hpp"
#include "player.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include "controller.hpp"

class Application {
public:
    Application();
    void RegisterStates();
    void ProcessInput();
    void Render();
    void Run();
    void Update(sf::Time dt);
private:
    sf::RenderWindow window_;
    sf::Vector2f viewOffset_;

     sf::Text	statisticsText_;

    TextureHolder textures_;
    FontHolder fonts_;
    Player player_;
    GUI::Container GUIContainer_;
    GUI::Controller GUIController_;
    StateStack stateStack_;
    
   

};
