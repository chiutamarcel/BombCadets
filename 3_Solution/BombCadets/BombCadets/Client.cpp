#include "Client.h"
#include "Map.h"
//#include "Common.h"
#include "Entities.h"
#include "GameConfig.h"

#include <iostream>

Client* Client::instance = nullptr;

Client::~Client()
{
}

Client::Client()
{
    hasStarted = false;
}

void Client::chatPrompt()
{
    std::string text;
    std::cin >> text;
    socket.send(text.c_str(), PACKETDATASIZE, sv_address, SERVER_PORT);
}

void Client::syncVelocities(sf::Packet packet)
{
    CommonNetworking::PacketType type;
    int _id;
    sf::Vector2f vel;

    if (!(packet >> type >> _id >> vel.x >> vel.y)) return;

    if (type != CommonNetworking::PacketType::VELOCITY) return;

    const std::vector<Character*>& characters = Entities::getInstance().getCharacters();

    //if (id <= 0 || id >= characters.size())
    //    throw "id out of bounds!";

    characters[_id]->setVelocity(vel);

}

void Client::sendLocalVelocity()
{
    sf::Packet packet;
    sf::Vector2f vel = Entities::getInstance().getCharacters()[id]->getVelocity();

    packet << CommonNetworking::PacketType::VELOCITY << id << vel.x << vel.y;

    send(packet);
}

void Client::sendPackets()
{
    sendLocalVelocity();
}

void Client::receivePackets()
{
    try {
        sf::Packet packet;
        
        receivePacket(packet);

        if (!packet) return;

        syncVelocities(packet);
    }
    catch (std::string e) {

    }
}

MapText Client::waitForMapInfo() {
    try {
        using namespace GameConfig;

        MapText mapText(BLOCKSONSCREENX, BLOCKSONSCREENY);
        sf::Packet packet;
        CommonNetworking::PacketType type;

        receivePacket(packet);

        if (!(packet >> type >> mapText))
            throw std::string("Unexpected packet!");
        if (type != CommonNetworking::PacketType::MAPINFO)
            throw std::string("Packet is not of type MAPINFO!");

        Map::spawnMap(mapText);

        return mapText;
    }
    catch (std::string e) {
        std::cout << e << std::endl;
        exit(1);
    }
}

void Client::connect()
{
    try {
        sf::Packet packet;

        std::cout << "Trying to connect to server..." << std::endl;

        packet << CommonNetworking::PacketType::MESSAGE << "connect";

        send(packet);

        packet.clear();

        std::string text;
        CommonNetworking::PacketType type;
        int _id;

        receivePacket(packet);

        if (!(packet >> type >> text >> _id)) {
            throw std::string("Server connection failed!");
        }

        if (!type == CommonNetworking::PacketType::MESSAGE) {
            return;
        }

        if (strcmp(text.c_str(), "connected")) {
            throw text;
        }

        id = _id;

        std::cout << "Server connection successful with id: " << id << std::endl;
    }
    catch (std::string e) {
        std::cout << e << std::endl;
        exit(1);
    }
}

void Client::disconnect()
{
}

Client& Client::getInstance()
{
    if (instance == nullptr) {
        instance = new Client();
    }

    return *instance;
}

void Client::deleteInstance()
{
    if (instance == nullptr) return;
    delete instance;
}

const bool& Client::getHasStarted()
{
    return hasStarted;
}

void Client::start()
{
    hasStarted = true;
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
    waitForMapInfo();
    socket.setBlocking(false);
}

void Client::update()
{
    if (hasStarted == true) {
        try {
            receivePackets();
        }
        catch (std::string e) {

        }
        sendPackets();
    }
}

void Client::pollEvents()
{
    
}

void Client::send(sf::Packet& packet)
{
    socket.send(packet, sv_address, SERVER_PORT);
}

void Client::receivePacket(sf::Packet& packet)
{
    sf::IpAddress sender_addr;
    unsigned short sender_port;

    socket.receive(packet, sender_addr, sender_port);

    if (sender_addr != sv_address.toString() || sender_port != SERVER_PORT) {
        return;
    }
}

const int& Client::getId()
{
    return id;
}

void Client::setId(int _id)
{
    id = _id;
}
