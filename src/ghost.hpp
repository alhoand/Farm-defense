#include "sprite_node.hpp"
#include "tower.hpp"

class Ghost : public SpriteNode {
public:
    Ghost(Tower::Type towerType, TextureHolder& textures, sf::Vector2f sideBarPos);
    void GetBack();
    unsigned int GetCategory() const;
    sf::Vector2f GetPosition() const;
    sf::Vector2f GetSideBarPos() const;
    void Drag();
    void UnDrag();
    bool IsDragged() const;
    sf::FloatRect GetBoundingRect() const;
    void Activate();
    void Deactivate();

private:
    void SetTransparent();
    void SetVisible();
    sf::Vector2f sideBarPos_;
    bool isDragged_;
    bool active_;

};