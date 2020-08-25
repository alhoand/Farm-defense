#pragma once

#include <SFML/System/Time.hpp>
#include <functional>
#include <cassert>     
#include "scene_node.hpp"
#include "category.hpp"
#include <cassert>
class SceneNode;

class GameField;

struct Command {
    Command();
    std::function<void(SceneNode&, sf::Time)> action_;
    std::function<void(GameField&, sf::Time)> gameFieldAction_;
    unsigned int category_;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> DerivedAction(Function fn) {
    return [=] (SceneNode& node, sf::Time dt) {
        //Check that there is a derived class "underneath"
        assert(dynamic_cast<GameObject*>(&node) != nullptr);
        // call the function given as parameter and forward the derived class
        fn(static_cast<GameObject&>(node), dt);
    };
}
template <typename Function>
std::function<void(GameField&, sf::Time)> GameFieldAction(Function fn) 
{
    return [=] (GameField& gameField, sf::Time dt) {
        fn(gameField, dt);
    };
};

