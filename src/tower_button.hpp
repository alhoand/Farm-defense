#include "button.hpp"
#include "tower_picture.hpp"

namespace GUI
{
    class TowerButton : public Button {
        public:
                            TowerButton(Tower::Type type, sf::Vector2f sidebarPos, const FontHolder& fonts, const TextureHolder& textures);
                            TowerButton(Tower::Type type, sf::Vector2f sidebarPos, const FontHolder& fonts, const TextureHolder& textures, sf::IntRect normalTexturePos, sf::IntRect selectedTexturePos);
        private:
            Tower::Type     type_;
            TowerPicture    towerPicture_;
            sf::Vector2f    sidebarPosition_;

    };
}
