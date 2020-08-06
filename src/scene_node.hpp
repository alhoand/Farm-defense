#pragma once

#include <SFML/Graphics.hpp>
#include "category.hpp"
#include "command.hpp"

#include <memory>
#include <vector>
#include <set>
#include <iostream>
#include <utility>


struct Command;

// Represents a transformable and drawable node in a scene graph
class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable {
public:
    typedef std::unique_ptr<SceneNode> Ptr;
    typedef std::pair<SceneNode*, SceneNode*> Pair;

    SceneNode();
    void AttachChild(Ptr node);
    Ptr DetachChild(const SceneNode& node);
    void Update(sf::Time dt);
    virtual unsigned int GetCategory() const;
    void OnCommand(const Command& command, sf::Time dt);
    sf::Transform GetWorldTransform() const;
    sf::Vector2f GetWorldPosition() const;
    void CheckNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);
    void CheckSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
    virtual bool IsDestroyed() const;
    virtual sf::FloatRect GetBoundingRect() const;

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

bool Collision(const SceneNode& lhs, const SceneNode& rhs);