#include "controller.hpp"
#include "tower_picture.hpp"
namespace GUI
{

Controller::Controller(sf::RenderWindow& window) :
window_(window)
{
}

void Controller::SendCommand(Command command)
{
   commandInbox_.Push(command); 
}

void Controller::FetchInput(CommandQueue& commands)
{
    while(!commandInbox_.IsEmpty())
    {
        commands.Push(commandInbox_.Pop());
    }
}


}
