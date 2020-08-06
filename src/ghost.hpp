#include "sprite_node.hpp"
#include "tower.hpp"

class Ghost : public SpriteNode {
public:
    Ghost(Tower::Type towerType, TextureHolder& textures, sf::Vector2f sideBarPos);
    void GetBack();
    unsigned int GetCategory() const;
    sf::Vector2f GetPosition() const;
    sf::Vector2f GetSideBarPos() const;
    void SetClicked(bool value);
    bool GetClicked() const;

private:
    sf::Vector2f sideBarPos_;
    bool clicked_;

};