#include <iostream>

#include "Game.h"
#include "Client.h"
//#include "MainMenu.h"
//#include "PlayMode.h"
//#include "AboutMode.h"

using namespace sf;

#define HEIGHT 832
#define WIDTH 1344

using namespace std;

int main()
{
    Game game;
    //Client client;

    game.start();
    //client.start();

    // Game Loop
    while (game.getWindow().isOpen())
    {
        game.pollEvents();
        game.update();
        //client.update();
        game.draw();
    }

    return EXIT_SUCCESS;
}