#include "Client.h"

#include <iostream>

#define CLIENT_PORT 54001
#define SERVER_PORT 54000

void Client::chatPrompt()
{
    std::string text;
    std::cin >> text;
    socket.send(text.c_str(), 100, sv_address, SERVER_PORT);
}

void Client::connect()
{
    char outdata[100] = "connect";
    char indata[100] = "";
    std::size_t received;
    unsigned short port;

    std::cout << "Trying to connect to server..." << std::endl;

    if (socket.send(outdata, 100, sv_address, SERVER_PORT) != sf::Socket::Done)
    {
        std::cout << "ERROR!" << std::endl;
        exit(1);
    }

    // NOTE: here the port is used to save the port!
    if (socket.receive(indata, 100, received, sv_address, port) != sf::Socket::Done)
    {
        std::cout << "ERROR!" << std::endl;
        exit(1);
    }

    // NOTE: Debug purposes only, delete this later!
    std::cout << indata << std::endl;

    // NOTE: here I should first check if the port is the server's
    if (strcmp(indata, "connected") != 0)
    {
        std::cout << "Server connection failed!" << std::endl;
        exit(1);
    }

    std::cout << "Server connection successful!" << std::endl;
}

void Client::start()
{
    socket.setBlocking(true);

    std::string sv_addr_str;
    std::cout << "Enter server address: " << std::endl;
    std::cin >> sv_addr_str;

    sv_address = sf::IpAddress(sv_addr_str);

    // bind the socket to a port
    if (socket.bind(CLIENT_PORT) != sf::Socket::Done)
    {
        std::cout << "ERROR BINDING TO SOCKET!" << std::endl;
        exit(1);
    }

    connect();
}

void Client::update()
{
    //chatPrompt();
}
