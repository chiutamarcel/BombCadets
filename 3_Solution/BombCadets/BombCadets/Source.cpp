#include <iostream>

#include "Game.h"

#define CLIENT_PORT 54001
#define SERVER_PORT 54000

using namespace std;

void receiveUDP(sf::UdpSocket& socket)
{
    char data[100] = "bababui";

    // UDP socket:
    sf::IpAddress recipient = "127.0.0.1";
    unsigned short port = SERVER_PORT;
    if (socket.send(data, 100, recipient, port) != sf::Socket::Done)
    {
        std::cout << "ERROR!" << std::endl;
        exit(1);
    }
}

int main()
{
    Game game;
    game.start();

    sf::UdpSocket socket;

    // bind the socket to a port
    if (socket.bind(CLIENT_PORT) != sf::Socket::Done)
    {
        std::cout << "ERROR!" << std::endl;
        exit(1);
    }

    // Game Loop
    while (game.getWindow().isOpen())
    {
        game.pollEvents();
        game.update();
        game.draw();
        receiveUDP(socket);
    }

    return EXIT_SUCCESS;
}