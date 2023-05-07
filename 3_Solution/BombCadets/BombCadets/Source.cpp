#include <iostream>

#include "Game.h"
#include "Client.h"

using namespace std;

int main()
{
    Game game;
    Client client;

    game.start();
    client.start();

    // Game Loop
    while (game.getWindow().isOpen())
    {
        game.pollEvents();
        game.update();
        client.update();
        game.draw();
    }

    return EXIT_SUCCESS;
}