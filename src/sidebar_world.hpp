#pragma once
#include <array>
#include <vector>
#include <SFML/System/NonCopyable.hpp>
#include "scene_node.hpp"
#include "command_queue.hpp"
#include "resource_holder.hpp"
#include "resource_identifiers.hpp"
#include <memory>


namespace GUI
{
    // Represents a sidebar GUI world, where there are multiple pictures of towers that can interact
class SidebarWorld : public sf::NonCopyable {
    public:
                            SidebarWorld(sf::RenderWindow& window, sf::Vector2f sidebarPosition);
        
        
        enum GUILayer {
            Background,
            Foreground,
            LayerCount
        };

        void                AddTowerPicture(SceneNode::Ptr towerPicture);
        void                OnCommand(Command command, sf::Time dt);
        void                Update(sf::Time dt);
        void                Draw();
        void                SetGraphPosition(sf::Transform parentTansform);
        CommandQueue&       GetCommandQueue();
    private:
        void                BuildScene();
        void                LoadTextures();
        sf::RenderWindow&   window_;
        sf::Vector2f        sidebarPosition_;
        TextureHolder       textures_;
        SceneNode           sceneGraph_;
        std::array<SceneNode*, LayerCount> sceneLayers_;
        CommandQueue        commandQueue_;


};
}