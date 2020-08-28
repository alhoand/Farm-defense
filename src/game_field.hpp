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
#include "data_tables.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics.hpp>

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
        int             GetCurrentLevel();
        bool            IsEndOfLevel();
        bool            IsEndOfGame();
        int             GetAddedMoney();
        void            NextEnemyWave();
        void            NextLevel();

        void AddTower(Tower::Type type, sf::Vector2f pos);

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
        sf::Time            spawnCountdown_ ;
        int                 spawnInterval_;
        int                 leftToSpawn_;
        std::vector<Enemy*> activeEnemies_;
        unsigned int        difficultyLevel_;
	    unsigned int        levelCount_; 
        sf::Time            levelBreakTimer_;
        int                 newEnemiesReachedEnd_;
        int                 roundMoney_;
        bool                hasActiveEntities_;
        bool                newLevelStarted_;
        bool                isEndOfLevel_;
        sf::IntRect         outOfBounds_;

};