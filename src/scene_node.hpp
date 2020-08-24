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
class CommandQueue;

// Represents a transformable and drawable node in a scene graph
class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable {
public:
    typedef std::unique_ptr<SceneNode> Ptr;
    typedef std::pair<SceneNode*, SceneNode*> Pair;

                            SceneNode(Category::Type category = Category::None);
    void                    AttachChild(Ptr node);
    Ptr                     DetachChild(const SceneNode& node);
    void                    Update(sf::Time dt, CommandQueue& commands);
    virtual unsigned int    GetCategory() const;
    void                    OnCommand(const Command& command, sf::Time dt);
    sf::Transform           GetWorldTransform() const;
    sf::Vector2f            GetWorldPosition() const;

    void                    CheckNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);
    void                    CheckSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
    virtual bool            IsDestroyed() const;
    virtual bool            IsMarkedForRemoval() const;
    void					RemoveDestroyedNodes();
    virtual sf::FloatRect   GetBoundingRect() const;

private:
    void			DrawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void    UpdateCurrent(sf::Time dt, CommandQueue& commands);
    void            UpdateChildren(sf::Time dt, CommandQueue& commands);
    virtual void    draw(sf::RenderTarget& target, sf::RenderStates states)  const override;
    virtual void    Draw(sf::RenderTarget& target, sf::RenderStates states) const final;
    virtual void    DrawCurrent(sf::RenderTarget&, sf::RenderStates) const;
    void            DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const;


    std::vector<Ptr> children_;
    SceneNode* parent_;
    Category::Type defaultCategory_;
};

bool Collision(const SceneNode& lhs, const SceneNode& rhs);
float Distance(const SceneNode& lhs, const SceneNode& rhs);

