#include "Server.h"
#include "Common.h"
#include "GameConfig.h"

#include <iostream>


Server::Server():
    mapText(GameConfig::BLOCKSONSCREENX, GameConfig::BLOCKSONSCREENY)
{

}

void Server::listenForConnections(sf::Packet packet, sf::IpAddress sender, unsigned short port)
{
    try {
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

        Client* client = spawnPlayer(sender.toString(), port);

        if (client == nullptr) {
            throw std::string("Could not spawn client: ") + sender.toString();
        }

        client->confirmConnection();
        client->sendMapInfo(mapText);
    }
    catch (std::string e) {
        std::cout << e << std::endl;
    }
    
}

void Server::listenForPositions(sf::Packet packet, sf::IpAddress sender, unsigned short port) {
    CommonNetworking::PacketType type;
    int id;
    sf::Vector2f pos;

    if (!(packet >> type >> id >> pos.x >> pos.y)) return;

    if (type != CommonNetworking::PacketType::POSITION) return;

    packet << type << id << pos.x << pos.y;

    for (auto client : connected_clients) {
        if (client->getIp() != sender) {
            client->send(packet);
        }
    }
}

Client* Server::spawnPlayer(std::string player_ip, unsigned short port)
{
    try {
        if (alreadyExists(player_ip, port) == true) {
            throw std::string("Client is already connected!");
        }

        sf::Packet packet;
        packet << CommonNetworking::PacketType::MESSAGE << "spawn_player";

        int id = connected_clients.size();

        Client* client = new Client(id, port, player_ip, &socket);
        
        // Notify all the other players that the player connected!
        for (auto c : connected_clients) {
            c->send(packet);
        }

        connected_clients.push_back(client);

        return client;
    }
    catch (std::string e) {
        std::cout << e << std::endl;
        return nullptr;
    }
    
}

//Client* Server::searchClientByIp(std::string player_ip)
//{
//    for (auto client : connected_clients) {
//        if (client->getIp() == player_ip)
//            return client;
//    }
//
//    return nullptr;
//}

bool Server::alreadyExists(std::string player_ip, unsigned short port)
{
    for (auto client : connected_clients) {
        if (client->getIp() == player_ip && client->getPort() == port) return true;
    }
    return false;
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

    mapText.readFromFile(GameConfig::mapFile);
    mapText.putBreakableBlocks(GameConfig::NRBREAKABLEWALLS);
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

    listenForPositions(packet, sender, port);
    //listenForVelocities(packet, sender);
    listenForConnections(packet, sender, port);
}
