#include "resource_holder.hpp"
#include "resource_identifiers.hpp"
#include "player.hpp"
#include "state_stack.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class Application {
    public:
        Application();
        void Run();

    private:
        void RegisterStates();
        void ProcessInput();
        void Update(sf::Time dt);
        void Render();
        void UpdateStatistics(sf::Time dt);

        static const sf::Time	TimePerFrame;

		sf::RenderWindow		window_;
		TextureHolder			textures_;
	  	FontHolder				fonts_;
		Player					player_;

		StateStack				stateStack_;

		sf::Text				statisticsText_;
		sf::Time				statisticsUpdateTime_;
		std::size_t				statisticsNumFrames_;
};