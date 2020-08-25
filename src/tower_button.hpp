#include "button.hpp"
#include "tower_picture.hpp"

namespace GUI
{
    class TowerButton : public Button {
        public:
                                // TowerButton(Tower::Type type, sf::Vector2f sidebarPos, const FontHolder& fonts, const TextureHolder& textures);
                                    TowerButton(Tower::Type type, sf::Vector2f sidebarPos, const FontHolder& fonts, const TextureHolder& textures, sf::IntRect normalTexturePos, sf::IntRect selectedTexturePos);
            Tower::Type             GetTowerType() const;
            virtual void            Update(sf::Time dt) override;
            void                    AddTowerPicture(TowerPicture*);
            TowerPicture*           GetTowerPic() const;
        private:
            virtual void	        Draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            Tower::Type             towerType_;
            TowerPicture*           towerPicture_;
            sf::Vector2f            sidebarPosition_;

    };
}
