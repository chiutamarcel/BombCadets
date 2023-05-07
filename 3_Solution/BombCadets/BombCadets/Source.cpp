#include <iostream>

#include "Game.h"

#define CLIENT_PORT 54001
#define SERVER_PORT 54000

using namespace std;

void connectToSv(sf::IpAddress& sv_address, unsigned short& port, sf::UdpSocket& socket)
{
    char outdata[100] = "connect";
    char indata[100] = "";
    std::size_t received;
    
    if (socket.send(outdata, 100, sv_address, port) != sf::Socket::Done)
    {
        std::cout << "ERROR!" << std::endl;
        exit(1);
    }

    if (socket.receive(indata, 100, received, sv_address, port) != sf::Socket::Done)
    {
        std::cout << "ERROR!" << std::endl;
        exit(1);
    }

    if (strcmp(indata, "connected") != 0)
    {
        std::cout << "Server connection failed!" << std::endl;
        exit(1);
    }
    
    std::cout << "Server connection successful!" << std::endl;
}

int main()
{
    Game game;
    game.start();

    sf::UdpSocket socket;
    socket.setBlocking(true);

    sf::IpAddress sv_address("127.0.0.1");
    unsigned short sv_port = SERVER_PORT;

    // bind the socket to a port
    if (socket.bind(CLIENT_PORT) != sf::Socket::Done)
    {
        std::cout << "ERROR!" << std::endl;
        exit(1);
    }

    connectToSv(sv_address, sv_port, socket);

    // Game Loop
    while (game.getWindow().isOpen())
    {
        game.pollEvents();
        game.update();
        game.draw();
    }

    return EXIT_SUCCESS;
}