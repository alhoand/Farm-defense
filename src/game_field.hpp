#pragma once

//Initial header file for gamefield class
#include <list>
#include <array>
#include <vector>
#include <memory>
#include "enemies/enemy.hpp"
#include "enemies/test_enemy.hpp"
#include "enemies/basic_enemy.hpp"
#include "tower.hpp"
#include "bullet.hpp"
#include "SFML/Graphics.hpp"
#include "sprite_node.hpp"
#include "command_queue.hpp"
#include "resource_holder.hpp"
#include "resource_identifiers.hpp"
#include "scene_node.hpp"
#include "command.hpp"
#include "category.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics.hpp>

/*  ***TODO***
* 
* - add multiple towers and enemies to the sceneGraph
* - move the towers with mouse
* - enemy move path
* - collision recognition
* - all return values are void, to be changed for right ones
*/
// Forward declaration
namespace sf {
	class RenderWindow;
}
// Takes care of building, updating and rendering the world to a SFML window
class GameField : private sf::NonCopyable {
    public:
        //Constructor
        explicit        GameField(sf::RenderWindow& window, sf::Vector2f viewOffset);
		
        //Update whole game field
        void            Update(sf::Time dt);
        void            Draw();
        CommandQueue&   GetCommandQueue();

        std::pair<SceneNode*, bool> GetActiveNode() const;

        //void AddTower(Tower* t); not implemented yet

    private:
        void            LoadTextures();
        void            BuildScene();
        void            HandleCollisions();
        void            SpawnEnemies(sf::Time dt);
        void            DestroyEntitiesOutsideView();
        sf::FloatRect   GetViewBounds() const;
        sf::FloatRect   GetGamefieldBounds() const;
        void            MakeTowersShoot();

        enum Layer {
            Background,
            Field,
            LayerCount
        };

        sf::RenderWindow&   window_;
        sf::Vector2f        viewOffset_;
        sf::View            gameFieldView_;
        TextureHolder       textures_;
        SceneNode           sceneGraph_;
        std::array<SceneNode*, LayerCount> sceneLayers_;
        sf::FloatRect       gameFieldBounds_;
        sf::Vector2f        spawnPosition_;
        CommandQueue        commandQueue_;
        float               enemySpeed_;
        //std::list<Tower*> towers_;
        Enemy*              firstEnemy_;
        Tower*              firstTower_;
        //std::list<Bullet*> bullets_;
        sf::Time            spawnCountdown_ ;
        int                 spawnInterval_;
        int                 leftToSpawn_; //initial, could change for better
        //std::vector<Tower*> shootingTowers_;
        std::vector<Enemy*> activeEnemies_;

};