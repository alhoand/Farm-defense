#include "sidebar_world.hpp"

namespace GUI
{
    SidebarWorld::SidebarWorld(sf::RenderWindow& window, sf::Vector2f sidebarPosition) :
    window_(window)
    , sidebarPosition_(sidebarPosition)
    , sceneGraph_()
    , sceneLayers_()
    , commandQueue_()
    {
        LoadTextures();
        BuildScene();
    }

void SidebarWorld::OnCommand(Command, sf::Time)
{
    // Do nothing for now
}


void SidebarWorld::BuildScene()
{
	for (std::size_t i = 0; i < LayerCount; i++) {
		Category::Type category = (i == Foreground) ? Category::Scene : Category::None;

		SceneNode::Ptr layer(new SceneNode(category));
		sceneLayers_[i] = layer.get();
		sceneGraph_.AttachChild(std::move(layer));
	}

    
}

void SidebarWorld::AddTowerPicture(SceneNode::Ptr towerPicture)
{
    sceneLayers_[Foreground]->AttachChild(std::move(towerPicture));
}

void SidebarWorld::Draw()
{
    window_.draw(sceneGraph_);
}

// This is to make all the towers to their correct positions in the sidebar
void SidebarWorld::SetGraphPosition(sf::Transform parentTansform)
{
    sceneGraph_.setPosition(parentTansform* sf::Vector2f()); //For now: this maybe a clumsy way to achieve this
}

// Update all the pictures of the towers in the sidebar GUI
void SidebarWorld::Update(sf::Time dt)
{
    while(!commandQueue_.IsEmpty()) {
        Command next = commandQueue_.Pop();
        if (next.category_ == Category::GameField)
        {
            OnCommand(next, dt);
        }
        else 
        {
            sceneGraph_.OnCommand(next, dt);
        }
    }

    sceneGraph_.Update(dt, commandQueue_);
}

CommandQueue& SidebarWorld::GetCommandQueue()
{
    return commandQueue_;
}

void SidebarWorld::LoadTextures()
{
    textures_.Load(Textures::ID::BasicTower, "../media/textures/tower.png");
	textures_.Load(Textures::ID::SuperTower, "../media/textures/harvester.png");
	textures_.Load(Textures::ID::SlowingTower, "../media/textures/tower.png");
	textures_.Load(Textures::ID::BombingTower, "../media/textures/tower.png");
}

}