#include "Server.h"

#include <iostream>

#define CLIENT_PORT 54001
#define SERVER_PORT 54000
#define MAX_CLIENTS 4

void Server::listenForConnections(const char indata[100], sf::IpAddress sender)
{
    if (strcmp(indata, "connect") != 0) {
        return;
    }

    if (connected_clients.size() >= 4) {
        std::cout << "Maximum nr of players reached!" << std::endl;
        return;
    }

    if (connected_clients.count(sender.toString()) == 0) {
        char outdata[100] = "connected";
        socket.send(outdata, 100, sender, CLIENT_PORT) != sf::Socket::Done;
        connected_clients.insert(sender.toString());
    }
    else {
        std::cout << "Player already connected!" << std::endl;
    }

    spawnPlayer(sender.toString());
}

void Server::spawnPlayer(std::string player_ip)
{
    const char data[100] = "spawn_player";

    for (auto client : connected_clients) {
        if (client != player_ip)
            socket.send(data, 100, client, CLIENT_PORT);
    }
}

void Server::start()
{
    std::cout << "Starting server..." << std::endl;

    // Binding socket
    if(socket.bind(SERVER_PORT) != sf::Socket::Done)
    {
        throw std::string("Could not bind socket!");
    }

    std::cout << "Server started successfully on port " << SERVER_PORT << std::endl;
}

void Server::update()
{
    char indata[100];
    std::size_t received;
    sf::IpAddress sender;
    unsigned short port;

    sf::Socket::Status status;

    status = socket.receive(indata, 100, received, sender, port);

    if (status != sf::Socket::Done)
    {
        throw std::string("Could not receive data from port ") + std::string(std::to_string(port));
    }
    std::cout << "Received " << received << " bytes from " << sender << " on port " << port << std::endl;
    std::cout << indata << std::endl;

    listenForConnections(indata, sender);
}
