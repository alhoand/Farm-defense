#include "tower_picture.hpp"
#include "data_tables.hpp"

namespace {
	const std::vector<TowerData> data = InitializeTowerData();
}

TowerPicture::TowerPicture(Tower::Type type, const TextureHolder& textures, sf::Vector2f sideBarPos)
    : SpriteNode(textures.Get(data[type].texture)), sideBarPos_(sideBarPos), isDragged_(false), active_(false)
 {

    setOrigin(sprite_.getLocalBounds().width/2.f, sprite_.getLocalBounds().height/2.f);

    setPosition(sideBarPos_);

   /* switch (type)
    {
    case Tower::Type::Super:
        sprite_.setScale(data[Tower::Type::Super].scale, data[Tower::Type::Super].scale);
        break;
    
    default:
        break;
    }*/
    //std::cout << "Tp origin is: " << getOrigin().x << ", " << getOrigin().y << std::endl;
    //std::cout << "Tp world pos is: " << GetWorldPosition().x << ", " << GetWorldPosition().y << std::endl;
    //std::cout << "Tp pos is: " << getPosition().x << ", " << getPosition().y << std::endl;
    //std::cout << "SidebarPos is " << sideBarPos_.x << ", " << sideBarPos_.y << std::endl;

  }
void TowerPicture::SetSidebarPos(sf::Vector2f pos)
{
    sideBarPos_ = pos;
}

void TowerPicture::SetClickPos(sf::Vector2f pos)
{
    clickPosition_ = pos;
}

sf::Vector2f TowerPicture::GetClickPos() const
{
    return clickPosition_;
}



void TowerPicture::GetBack() {
    Deactivate();

   /* std::cout << "TowerPic origin:" << getOrigin().x << ", " << getOrigin().y << std::endl;
    std::cout << "TowerPic world pos:" << GetWorldPosition().x << ", " << GetWorldPosition().y << std::endl;
    std::cout << "TowerPic pos:" << getPosition().x << ", " << getPosition().y << std::endl;
    std::cout << "TowerPic Getpos:" << GetPosition().x << ", " << GetPosition().y << std::endl;
    std::cout << "TowePic Local bounds center " << sprite_.getLocalBounds().width/2.f << ", " << sprite_.getLocalBounds().height/2.f << std::endl;
    */
    setOrigin(sprite_.getLocalBounds().width/2.f, sprite_.getLocalBounds().height/2.f);
    /*std::cout << "TowePic Local bounds center after" << sprite_.getLocalBounds().width/2.f << ", " << sprite_.getLocalBounds().height/2.f << std::endl;
    std::cout << "TowerPic origin after: " << getOrigin().x << ", " << getOrigin().y << std::endl;
    sf::Vector2f parent = GetWorldPosition() - getPosition();
    std::cout << "parent pos: " << parent.x << ", "  << parent.y << std::endl;
    */
    setPosition(sideBarPos_); //+ (GetWorldTransform() * sf::Vector2f())); //- getPosition()));
    /*std::cout << "TowerPic world pos after: " << GetWorldPosition().x << ", " << GetWorldPosition().y << std::endl;
    std::cout << "TowerPic pos after: " << getPosition().x << ", " << getPosition().y << std::endl;
    std::cout << "TowerPic Getpos: after " << GetPosition().x << ", " << GetPosition().y << std::endl;
*/
    //SetTransparent();
}

unsigned int TowerPicture::GetCategory() const {
    return Category::TowerPicture;
}

sf::Vector2f TowerPicture::GetPosition() const {
    sf::Transform transform = GetWorldTransform();//getTransform();
    return transform * sf::Vector2f();
}



bool TowerPicture::Drag() {
    //sprite_.setColor(sf::Color(255, 255, 255, 128));
    if (IsActive())
        isDragged_ = true;
    return IsActive();
}

void TowerPicture::UnDrag() {
    isDragged_ = false;
}
bool TowerPicture::IsDragged() const {
    return isDragged_;
}

sf::Vector2f TowerPicture::GetSidebarPos() const {
    return sideBarPos_;
}

void TowerPicture::Activate()
{
    active_ = true;
}

void TowerPicture::Deactivate()
{
    active_ = false;
}

bool TowerPicture::IsActive() const
{
    return active_;
}


sf::FloatRect TowerPicture::GetBoundingRect() const {
    sf::Transform transform = GetWorldTransform();//getTransform();
    return transform.transformRect(sprite_.getGlobalBounds()); 
}


void TowerPicture::SetTransparent() {
    sprite_.setColor(sf::Color(255, 255, 255, 0)); //transparent
/*    sf::CircleShape range;
    range.setFillColor(sf::Color(255, 0, 0, 128));
    range.setOrigin(range.getLocalBounds().width/2.f, range.getLocalBounds().height);
    range.setPosition(getPosition()); */
}


void TowerPicture::SetVisible() {
    sprite_.setColor(sf::Color(255, 255, 255, 255));
}

void DrawTowerPicture(const TowerPicture& towerPicture, sf::RenderTarget& target, sf::RenderStates states)
{

    states.transform *= towerPicture.getTransform();

    target.draw(towerPicture.sprite_, states);
}

void TowerPicture::Update(sf::Time)
{
    // Here would be some update code if need be
}
