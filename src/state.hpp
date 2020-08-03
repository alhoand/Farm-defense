#pragma once

#include <memory>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "resource_identifiers.hpp"
#include "state_identifiers.hpp"
#include <SFML/System/Vector2.hpp>

namespace sf {
    class RenderWindow;
}
class Player;

class StateStack;

class State {
public:
    typedef std::unique_ptr<State> Ptr; // We use pointers a lot since State is abstract
    struct Context {
        Context(sf::RenderWindow &window,
                 TextureHolder &textures,
                 FontHolder& fonts_,
                 Player &player,
                 sf::Vector2f viewOffset
        );

        sf::RenderWindow* window_;
        TextureHolder* textures_;
        FontHolder* fonts_;
        Player* player;
        sf::Vector2f viewOffset_;
    };

    State(StateStack& stack, Context context);

    virtual ~State();

    virtual void Draw() = 0;

    virtual bool Update(sf::Time dt) = 0;

    virtual bool HandleEvent(const sf::Event &event);

protected:
    void RequestStackPush(States::ID stateID);
    void RequestStackPop();
    void RequestStateClear();

    Context GetContext() const;


private:
    Context context_;
    StateStack stateStack_;

};
