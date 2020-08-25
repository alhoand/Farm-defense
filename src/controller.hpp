#pragma once
#include "command_queue.hpp"
#include "category.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

namespace GUI {
// Represents a simple "source of control" that relays messages to the GameField from GUI
class Controller {
    public:
                            Controller(sf::RenderWindow& window);

    // Puts its own commands to the command queue given as parameter.
    // The caller then gains access to whatever commands the controller has.
        void                FetchInput(CommandQueue& commands);

    // Stores the given command.
    // Now future clients can fetch this command by calling FetchInput(...).
    // Therefore the caller of this function can "send" commands to future clients.
    // Used to send commands from the GUI sidebar to the game world (e.g. tower addition).
        void                SendCommand(Command command);

    // Handles the event and adds Commands to the @param commands
   //   void                HandleEvent(const sf::Event& event, CommandQueue& commands);

    private:
        sf::RenderWindow&   window_;
        CommandQueue        commandInbox_;

};

}

