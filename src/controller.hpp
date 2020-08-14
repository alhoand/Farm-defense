#pragma once
#include "command_queue.hpp"
#include "category.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

namespace GUI {
    
class Controller {
public:
    Controller();
    // Relays its own commands to the caller's queue
    void HandleSidebarInput(CommandQueue& commands);

    //Adds the command given as parameter to its own queue
    void SendCommand(Command command);

private:
    CommandQueue commandInbox_;

};

}

