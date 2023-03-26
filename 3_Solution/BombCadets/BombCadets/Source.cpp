#include <iostream>

#include "Game.h"

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
        game.draw();
    }

    return EXIT_SUCCESS;
}