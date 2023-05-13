#include <iostream>

#include "Game.h"
//#include "MainMenu.h"
//#include "PlayMode.h"
//#include "AboutMode.h"

using namespace sf;

#define HEIGHT 832
#define WIDTH 1344

using namespace std;

void main(int argc, char* argv[])
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

}