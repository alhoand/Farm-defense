#pragma once

#include <SFML/System/Time.hpp>
#include <functional>
#include <cassert>     
#include "scene_node.hpp"
#include "category.hpp"
#include <cassert>

class SceneNode;

struct Command {
    Command();
    std::function<void(SceneNode&, sf::Time)> action_;
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

