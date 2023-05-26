#include <iostream>

#include "Game.h"
#include "Client.h"
#include "Logger.h"
//#include "MainMenu.h"
//#include "PlayMode.h"
//#include "AboutMode.h"

using namespace sf;

using namespace std;

int main()
{
    Game game;

    game.start();

    // Game Loop
    while (game.getWindow().isOpen())
    {
        game.pollEvents();
        game.update();
        Client::getInstance().update();
        game.draw();
    }

    Client::deleteInstance();    
    
    return EXIT_SUCCESS;
}