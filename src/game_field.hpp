#pragma once

//Initial header file for abstract tower class
#include <list>
#include <array>
#include <memory>
#include "enemy.hpp"
#include "tower.hpp"
#include "bullet.hpp"
#include "SFML/Graphics.hpp"
#include "sprite_node.hpp"
/*  ***TODO***
* 
* - add multiple towers and enemies to the sceneGraph
* - move the towers with mouse
* - enemy move path
* - collision recognition
* - all return values are void, to be changed for right ones
*/
// Forward declaration
namespace sf
{
	class RenderWindow;
}
// Takes care of building, updating and rendering the world to a SFML window
class GameField : private sf::NonCopyable {
    public:
        //Constructor
        explicit GameField(sf::RenderWindow& window);
		
        //Update whole game field
        void Update(sf::Time dt);

        void Draw();

        //void AddTower(Tower* t); not implemented yet

    private:
        void LoadTextures();
        void BuildScene();

        enum Layer {
            Background,
            Ground,
            LayerCount
        };

        sf::RenderWindow& window_;
        sf::View gameFieldView_;
        TextureHolder textures_;
        SceneNode sceneGraph_;
        std::array<SceneNode*, LayerCount> sceneLayers_;
        sf::FloatRect gameFieldBounds_;
        sf::Vector2f spawnPosition_;
        float enemySpeed_;
        //std::list<Tower*> towers_;
        Enemy* firstEnemy_;
        //std::list<Bullet*> bullets_;
};