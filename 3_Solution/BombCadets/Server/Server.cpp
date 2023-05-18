#include "Server.h"
#include "Common.h"

#include <iostream>



void Server::listenForConnections(sf::Packet packet, sf::IpAddress sender)
{
    if (!packet) return;

    CommonNetworking::PacketType packetType;
    std::string text;

    packet >> packetType;

    if (packetType != CommonNetworking::PacketType::MESSAGE) {
        return;
    }

    packet >> text;

    if (strcmp(text.c_str(), "connect") != 0) {
        return;
    }

    if (connected_clients.size() >= MAX_CLIENTS) {
        std::cout << "Maximum nr of players reached!" << std::endl;
        return;
    }

    if (searchClientByIp(sender.toString()) == nullptr) {
        sf::Packet packet;
        int id = connected_clients.size();
        packet << CommonNetworking::PacketType::MESSAGE << "connected" << id;
        Client* client = spawnPlayer(sender.toString());
        client->send(packet);
    }
    else {
        std::cout << "Player already connected!" << std::endl;
    }

    
}

void Server::listenForVelocities(sf::Packet packet, sf::IpAddress sender)
{
    CommonNetworking::PacketType type;
    int id;
    sf::Vector2f vel;

    if (!(packet >> type >> id >> vel.x >> vel.y)) return;

    if (type != CommonNetworking::PacketType::VELOCITY) return;

    packet << type << id << vel.x << vel.y;

    for (auto client : connected_clients) {
        if (client->getIp() != sender) {
            client->send(packet);
        }
    }
}

Client* Server::spawnPlayer(std::string player_ip)
{
    try {
        sf::Packet packet;
        packet << CommonNetworking::PacketType::MESSAGE << "spawn_player";

        int id = connected_clients.size();

        Client* client = new Client(id, player_ip, &socket);
        
        // Notify all the other players that the player connected!
        for (auto c : connected_clients) {
            c->send(packet);
        }

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
    sf::Packet packet;
    sf::IpAddress sender;
    unsigned short port;

    sf::Socket::Status status;

    status = socket.receive(packet, sender, port);

    for (auto client : connected_clients) {
        client->update();
    }

    listenForVelocities(packet, sender);
    listenForConnections(packet, sender);
}
