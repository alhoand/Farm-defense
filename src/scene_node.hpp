#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "category.hpp"
#include "command.hpp"
#include <iostream>


struct Command;

// Represents a transformable and drawable node in a scene graph
class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable {
public:
    typedef std::unique_ptr<SceneNode> Ptr;
    SceneNode();
    void AttachChild(Ptr node);
    Ptr DetachChild(const SceneNode& node);
    void Update(sf::Time dt);
    virtual unsigned int GetCategory() const;
    void OnCommand(const Command& command, sf::Time dt);
    sf::Transform GetWorldTransform() const;
    sf::Vector2f GetWorldPosition() const;
private:
    virtual void UpdateCurrent(sf::Time dt);
    void UpdateChildren(sf::Time dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)  const override;
    virtual void Draw(sf::RenderTarget& target, sf::RenderStates states) const final;
    virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

    std::vector<Ptr> children_;
    SceneNode* parent_;
};