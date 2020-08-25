#include "tower_button.hpp"
namespace GUI
{
TowerButton::TowerButton(Tower::Type type,
                        sf::Vector2f sidebarPos,
                        const FontHolder& fonts,
                        const TextureHolder& textures,
                        sf::IntRect normalTexturePos,
                        sf::IntRect selectedTexturePos)   :
                        Button(fonts, textures, normalTexturePos, selectedTexturePos)
                        , towerType_(type)
                        , towerPicture_()
                        , sidebarPosition_(sidebarPos)
    {
           //sets origin to the globalbound center 
        Button::setOrigin(GetGlobalBounds().width/2.f, GetGlobalBounds().height/2.f);
        // Initializes a new TowerPicture
        //std::cout << "Here we are in tower pic" << std::endl;
        //std::unique_ptr<TowerPicture> towerPic(new TowerPicture(type, textures, sidebarPosition_));
        //towerPicture_ = std::move(towerPic);
        //towerPicture_->setPosition(sidebarPosition_ + GetWorldPosition());
        //towerPicture_->setPosition(-500.f, 5.f);
        //std::cout << "TowerPic pos: " << towerPicture_->getPosition().x << ", " << towerPicture_->getPosition().y << std::endl;
        //std::cout << "TowerPic origin: " << towerPicture_->getOrigin().x << ", " << towerPicture_->getOrigin().y << std::endl;
        //std::cout << "TowerPic world pos: " << towerPicture_->GetWorldPosition().x << ", " << towerPicture_->GetWorldPosition().y << std::endl;

        std::cout << "TowerButton pos: " << getPosition().x << ", " << getPosition().y << std::endl;
        std::cout << "TowerButton origin: " << getOrigin().x << ", " << getOrigin().y << std::endl;
        std::cout << "TowerButton world pos: " << GetWorldPosition().x << ", " << GetWorldPosition().y << std::endl;

    }

Tower::Type TowerButton::GetTowerType() const
{
        return towerType_;
}
TowerPicture* TowerButton::GetTowerPic() const
{
        return towerPicture_;
}
void TowerButton::Draw(sf::RenderTarget& target, sf::RenderStates states) const
{
        Button::Draw(target, states);
        //if (towerPicture_)
                //DrawTowerPicture(*towerPicture_, target, states);
}

void TowerButton::Update(sf::Time)
{
        //towerPicture_->Update(dt);
        
}

void TowerButton::AddTowerPicture(TowerPicture* tp)
{
        towerPicture_ = tp;
}


}