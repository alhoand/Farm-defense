#pragma once

#include <SFML/System/Time.hpp>
#include <functional>
#include "scene_node.hpp"
#include "category.hpp"

class SceneNode;

struct Command {
    Command();
    std::function<void(SceneNode&, sf::Time)> action_;
    unsigned int category_;
};

// Helper function template for downcasting SceneNodes to GameObjects such as Tower.
// Used when giving commands to game objects
template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> DerivedAction(Function fn) {
    return [=] (SceneNode& node, sf::Time dt) {
        //Check that there is a derived class "underneath"
        assert(dynamic_cast<GameObject*>(&node) != nullptr);
        // call the function given as parameter and forward the derived class
        fn(static_cast<GameObject&>(node), dt);
    };
};

