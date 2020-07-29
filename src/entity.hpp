#include <SFML/Graphics.hpp>
#include "scene_node.hpp"

// A thing that has a velocity
// It can move and be drawn on the screen since it is derived form SceneNode
class Entity : public SceneNode {
public:
    void                SetVelocity(sf::Vector2f velocity);
    void                SetVelocity(float vx, float vy);
    sf::Vector2f        GetVelocity() const;

protected: 
    virtual void UpdateCurrent(sf::Time dt);
private:
    sf::Vector2f        velocity_;
};