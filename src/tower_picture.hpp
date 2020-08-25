#include "sprite_node.hpp"
#include "towers/tower.hpp"

class TowerPicture : public SpriteNode {
    friend void             DrawTowerPicture(const TowerPicture& towerPicture, sf::RenderTarget& target, sf::RenderStates states);
    
    public:
                                            TowerPicture(Tower::Type towerType, const TextureHolder& textures, sf::Vector2f sideBarPos);
        void                                GetBack();
        unsigned int                        GetCategory() const override;
        sf::Vector2f                        GetPosition() const;
        sf::Vector2f                        GetSidebarPos() const;
        void                                SetSidebarPos(sf::Vector2f pos);
        void                                SetClickPos(sf::Vector2f pos);
        sf::Vector2f                        GetClickPos() const;

        void                                Drag();
        void                                UnDrag();
        bool                                IsDragged() const;
        
        sf::FloatRect                       GetBoundingRect() const override;
        void                                Activate();
        void                                Deactivate();
        void                                Update(sf::Time dt) override;

    private:

        void                                SetTransparent();
        void                                SetVisible();
        sf::Vector2f                        sideBarPos_;
        bool                                isDragged_;
        bool                                active_;
        sf::Vector2f                        clickPosition_;

};