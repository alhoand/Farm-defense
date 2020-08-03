#include "state.hpp"
#include "state_stack.hpp"

State::Context(sf::RenderWindow &window, TextureHolder& textures, FontHolder& fonts, Player& player, sf::Vector2f viewOffset) 
        : window_(&window),  textures_(&textures), fonts_(&fonts), player_(&player), viewOffset_(viewOffset) { }
