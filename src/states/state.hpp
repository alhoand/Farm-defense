#pragma once

#include <memory>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "../resource_identifiers.hpp"
#include "../state_identifiers.hpp"
#include <SFML/System/Vector2.hpp>
#include "../node_component.hpp"
#include <map>
#include "../gui_identifiers.hpp"
#include "../container.hpp"

namespace sf {
    class RenderWindow;
}
class Player;

class StateStack;

class State {
public:
    typedef std::unique_ptr<State> Ptr; // We use pointers a lot since State is abstract
    struct Context {
        Context(sf::RenderWindow& window,
                 TextureHolder& textures,
                 FontHolder& fonts_,
                 Player& player,
                 sf::Vector2f viewOffset,
                 GUI::Container& GUIContainer
        );

        sf::RenderWindow* window_;
        TextureHolder* textures_;
        FontHolder* fonts_;
        Player* player_;
        sf::Vector2f viewOffset_;
        GUI::Container* GUIContainer_;
        
    };

    State(StateStack& stack, Context context);

    virtual ~State() { }

    virtual void Draw() = 0;

    virtual bool Update(sf::Time dt) = 0;

    virtual bool HandleEvent(const sf::Event &event) = 0;

protected:
    void RequestStackPush(States::ID stateID);
    void RequestStackPop();
    void RequestStateClear();

    Context GetContext() const;


private:
    Context context_;
    StateStack* stateStack_;
};
