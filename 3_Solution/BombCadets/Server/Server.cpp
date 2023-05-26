#include "Server.h"
#include "Common.h"
#include "GameConfig.h"
#include "Logger.h"

#include <iostream>

Server* Server::instance = nullptr;

Server::Server():
    mapText(GameConfig::BLOCKSONSCREENX, GameConfig::BLOCKSONSCREENY)
{
    hasGameStarted = false;
}

Server::~Server()
{
}

void Server::endGame(int loserId)
{
    std::cout << "Game ended, loser: " << loserId << std::endl;
	Logger::getInstance()->log(LogLevel::INFO, "Game ended, loser: " + std::to_string(loserId));

    sf::Packet packet;

    packet << CommonNetworking::PacketType::LOSER << loserId;

    for (auto client : connected_clients) {
        client->send(packet);
    }

    hasGameStarted = false;
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
			Logger::getInstance()->log(LogLevel::INFO, "Maximum nr of players reached!");
            return;
        }

        Client* client = spawnPlayer(sender.toString(), port);

        if (client == nullptr) {
			Logger::getInstance()->log(LogLevel::ERROR, "Could not spawn client: " + sender.toString());
            throw std::string("Could not spawn client: ") + sender.toString();
        }

        client->confirmConnection();
        client->sendMapInfo(mapText);
    }
    catch (std::string e) {
        std::cout << e << std::endl;
    }
    
    
}

void Server::listenForKillRequests(sf::Packet packet, sf::IpAddress sender, unsigned short port)
{
    CommonNetworking::PacketType type;
    int id;
    int targetId;

    if (!(packet >> type >> id >> targetId)) return;

    if (type != CommonNetworking::PacketType::KILLVOTE) return;

    connected_clients[targetId]->getKillVoted(id, getPlayerCount());

    std::cout << "Client " << targetId << " was killvoted by " << id << std::endl;
	Logger::getInstance()->log(LogLevel::INFO, "Client " + std::to_string(targetId) + " was killvoted by " + std::to_string(id));
}

//void Server::listenForPositions(sf::Packet packet, sf::IpAddress sender, unsigned short port) {
//    CommonNetworking::PacketType type;
//    int id;
//    sf::Vector2f pos;
//
//    if (!(packet >> type >> id >> pos.x >> pos.y)) return;
//
//    if (type != CommonNetworking::PacketType::POSITION) return;
//
//    packet << type << id << pos.x << pos.y;
//
//    for (auto client : connected_clients) {
//        if (client->getIp() != sender || client->getPort() != port) {
//            client->send(packet);
//        }
//    }
//}
//
//void Server::listenForBombs(sf::Packet packet, sf::IpAddress sender, unsigned short port)
//{
//    CommonNetworking::PacketType type;
//    int id;
//    sf::Vector2f bombPos;
//
//    if (!(packet >> type >> id >> bombPos.x >> bombPos.y)) return;
//
//    if (type != CommonNetworking::PacketType::BOMB) return;
//
//    packet << type << id << bombPos.x << bombPos.y;
//
//    for (auto client : connected_clients) {
//        if (client->getIp() != sender || client->getPort() != port) {
//            client->send(packet);
//        }
//    }
//}

void Server::forwardPackets(sf::Packet packet, sf::IpAddress sender, unsigned short port)
{
    CommonNetworking::PacketType type;

    if (!(packet >> type)) return;

    if 
    (
        (type != CommonNetworking::PacketType::BOMB) &&
        (type != CommonNetworking::PacketType::POSITION)
    ) 
        return;

    packet << type;

    for (auto client : connected_clients) {
        if (client->getIp() != sender || client->getPort() != port) {
            client->send(packet);
        }
    }
}

Client* Server::spawnPlayer(std::string player_ip, unsigned short port)
{
    try {
        if (alreadyExists(player_ip, port) == true) {
			Logger::getInstance()->log(LogLevel::ERROR, "Client is already connected!");
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
    hasGameStarted = true;
    std::cout << "Starting server..." << std::endl;
	Logger::getInstance()->log(LogLevel::INFO, "Starting server...");

    // Binding socket
    if(socket.bind(SERVER_PORT) != sf::Socket::Done)
    {
        throw std::string("Could not bind socket!");
		Logger::getInstance()->log(LogLevel::ERROR, "Could not bind socket!");
    }

    std::cout << "Server started successfully on port " << SERVER_PORT << std::endl;
	Logger::getInstance()->log(LogLevel::INFO, "Server started successfully on port " + std::to_string(SERVER_PORT));

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

    listenForConnections(packet, sender, port);

    for (auto client : connected_clients) {
        client->update();
    }

    if (hasGameStarted == true) {
        listenForKillRequests(packet, sender, port);
        forwardPackets(packet, sender, port);
    }
}

int Server::getPlayerCount()
{
    return connected_clients.size();
}
    

Server& Server::getInstance()
{
    if (instance == nullptr) {
        instance = new Server();
    }

    return *instance;
}

void Server::deleteInstance()
{
    Logger::getInstance()->log(LogLevel::INFO, "Closing server...");
    if (instance != nullptr)
        delete instance;
}

const bool& Server::getHasMatchStarted() const
{
    return hasGameStarted;
}
