#pragma once

//Initial header file for gamefield class
#include <list>
#include <array>
#include <vector>
#include <memory>

#include "enemies/enemy.hpp"
#include "enemies/basic_enemy.hpp"
#include "enemies/bulk_enemy.hpp"
#include "enemies/multi_enemy.hpp"
#include "enemies/fast_enemy.hpp"

#include "towers/basic_tower.hpp"
#include "towers/super_tower.hpp"
#include "towers/slowing_tower.hpp"
#include "towers/bombing_tower.hpp"

#include "towers/bullet.hpp"
#include "sprite_node.hpp"
#include "command_queue.hpp"
#include "resource_holder.hpp"
#include "resource_identifiers.hpp"
#include "scene_node.hpp"
#include "category.hpp"
#include "utility.hpp"

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

struct Command;
// Takes care of building, updating and rendering the world to a SFML window
class GameField : private sf::NonCopyable {
    public:
        //Constructor
        explicit        GameField(sf::RenderWindow& window, sf::Vector2f viewOffset);
		
        //Update whole game field
        void            Update(sf::Time dt);
        void            Draw();
        CommandQueue&   GetCommandQueue();
        int             NewEnemiesReachedEnd();
        bool            IsEndOfLevel();
        bool            IsEndOfGame();
        void            AddRoundScore(int points);
        int             GetRoundScore();
        void            NextEnemyWave();
        void            NextLevel();

       // std::pair<SceneNode*, bool> GetActiveNode() const; not needed currently

        void AddTower(Tower::Type type, sf::Vector2f pos); //not implemented yet

    private:
        void            LoadTextures();
        void            BuildScene();
        void            BuildPath();
        void            HandleCollisions();
        void            SpawnEnemies(sf::Time dt);
        void            RandomEnemySpawner(unsigned int level);
        void            DestroyEntitiesOutsideView();
        sf::FloatRect   GetViewBounds() const;
        sf::FloatRect   GetGamefieldBounds() const;
        void            MakeTowersShoot();
       // void            HandleActiveTower();
        void            OnCommand(Command command, sf::Time dt);
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
        //std::list<Tower*> towers_;
        //std::list<Bullet*> bullets_;
        sf::Time            spawnCountdown_ ;
        int                 spawnInterval_;
        int                 leftToSpawn_; //initial, could change for better
        std::vector<Enemy*> activeEnemies_;
        // std::vector<Tower*> activeTowers_;
        unsigned int        difficultyLevel_;
	    unsigned int        levelCount_; //total amount of levels or waves in current game
        sf::Time            levelBreakTimer_;
        int                 newEnemiesReachedEnd_;
        int                 roundScore_;
        bool                hasActiveEnemies_;
        bool                newLevelStarted_;

};