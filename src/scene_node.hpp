#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#pragma once


// Represents a transformable and drawable node in a scene graph
class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable {
public:
    typedef std::unique_ptr<SceneNode> Ptr;
    SceneNode();
    void AttachChild(Ptr node);
    Ptr DetachChild(const SceneNode& node);
    void Update(sf::Time dt);
private:
    virtual void UpdateCurrent(sf::Time dt);
    void UpdateChildren(sf::Time dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)  const override;
    virtual void Draw(sf::RenderTarget& target, sf::RenderStates states) const final;
    virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Transform GetWorldTransform() const;
    sf::Vector2f GetWorldPosition() const;
    std::vector<Ptr> children_;
    SceneNode* parent_;
};