#include "controller.hpp"
namespace GUI
{

Controller::Controller()
{
}

void Controller::SendCommand(Command command)
{
   commandInbox_.Push(command); 
}

void Controller::HandleSidebarInput(CommandQueue& commands)
{
    while(!commandInbox_.IsEmpty())
    {
        commands.Push(commandInbox_.Pop());
    }
}

/*void Controller::HandleGUIMouseInput(const sf::Event& event, )*/

}
