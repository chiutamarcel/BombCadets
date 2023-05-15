#include "Server.h"
#include "Common/Common.h"

#include <iostream>



void Server::listenForConnections(const char indata[100], sf::IpAddress sender)
{
    if (strcmp(indata, "connect") != 0) {
        return;
    }

    if (connected_clients.size() >= MAX_CLIENTS) {
        std::cout << "Maximum nr of players reached!" << std::endl;
        return;
    }

    if (searchClientByIp(sender.toString()) == nullptr) {
        sf::Packet packet;
        packet << "connected";
        Client* client = spawnPlayer(sender.toString());
        client->send(packet);
    }
    else {
        std::cout << "Player already connected!" << std::endl;
    }

    
}

Client* Server::spawnPlayer(std::string player_ip)
{
    try {
        sf::Packet packet;
        packet << "spawn_player";

        Client* client = new Client(player_ip, &socket);
        client->send(packet);
        connected_clients.push_back(client);

        return client;
    }
    catch (...) {
        return nullptr;
    }
    
}

Client* Server::searchClientByIp(std::string player_ip)
{
    for (auto client : connected_clients) {
        if (client->getIp() == player_ip)
            return client;
    }

    return nullptr;
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

    status = socket.receive(indata, PACKETDATASIZE, received, sender, port);

    if (status != sf::Socket::Done)
    {
        throw std::string("Could not receive data from port ") + std::string(std::to_string(port));
    }
    std::cout << "Received " << received << " bytes from " << sender << " on port " << port << std::endl;
    std::cout << indata << std::endl;

    listenForConnections(indata, sender);
}
