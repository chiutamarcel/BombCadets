#include "Client.h"

#include "Map.h"
//#include "Common.h"
#include "Entities.h"
#include "GameConfig.h"

#include <iostream>

Client* Client::instance = nullptr;

#define positionUpdateRate 100 // milliseconds
#define positionSmoothRate 10

Client::~Client()
{
}

Client::Client()
{
    id = -1;
    hasStarted = false;
}

void Client::chatPrompt()
{
    std::string text;
    std::cin >> text;
    socket.send(text.c_str(), PACKETDATASIZE, sv_address, SERVER_PORT);
}

//void Client::syncVelocities(sf::Packet packet)
//{
//    CommonNetworking::PacketType type;
//    int _id;
//    sf::Vector2f vel;
//
//    if (!(packet >> type >> _id >> vel.x >> vel.y)) return;
//
//    if (type != CommonNetworking::PacketType::VELOCITY) return;
//
//    const std::vector<Character*>& characters = Entities::getInstance().getCharacters();
//
//    //if (id <= 0 || id >= characters.size())
//    //    throw "id out of bounds!";
//
//    characters[_id]->setVelocity(vel);
//
//}

void Client::syncPositions(sf::Packet packet) {
    CommonNetworking::PacketType type;
    int _id;
    sf::Vector2f pos;

    if (!(packet >> type >> _id >> pos.x >> pos.y)) return;

    if (type != CommonNetworking::PacketType::POSITION) return;

    (*characters)[_id]->setTargetPos(pos);
}

void Client::sendLocalVelocity()
{
    sf::Packet packet;
    sf::Vector2f vel = Entities::getInstance().getCharacters()[id]->getVelocity();
    

    packet << CommonNetworking::PacketType::VELOCITY << id << vel.x << vel.y;

    send(packet);
}

void Client::sendLocalPosition() {
    sf::Time time = lastPositionTimer.getElapsedTime();

    if (time.asMilliseconds() < positionUpdateRate) return;

    lastPositionTimer.restart();

    sf::Packet packet;
    sf::Vector2f pos = Entities::getInstance().getPlayer().getPosition();

    packet << CommonNetworking::PacketType::POSITION << id << pos.x << pos.y;

    send(packet);
}

void Client::sendBombPacket(sf::Vector2f bombPos)
{
    if (hasStarted == false)
        return;

    sf::Packet packet;

    packet << CommonNetworking::PacketType::BOMB << id << bombPos.x << bombPos.y;

    send(packet);
}

void Client::sendKillRequest(int targetId)
{
    if (hasStarted == false)
        return;

    sf::Packet packet;

    packet << CommonNetworking::PacketType::KILLVOTE << id << targetId;

    send(packet);
}

void Client::sendPackets()
{
    //sendLocalVelocity();
    sendLocalPosition();
}

void Client::receivePackets()
{
    try {
        sf::Packet packet;
        
        receivePacket(packet);

        if (!packet) return;

        //syncVelocities(packet);
        listenForLoser(packet);
        listenForBombPacket(packet);
        syncPositions(packet);
    }
    catch (std::string e) {

    }
}

void Client::listenForBombPacket(sf::Packet packet)
{
    CommonNetworking::PacketType type;
    int _id;
    sf::Vector2f bombPos;

    if (!(packet >> type >> _id >> bombPos.x >> bombPos.y)) return;

    if (type != CommonNetworking::PacketType::BOMB) return;

    Entities::getInstance().spawnBomb(bombPos);
}

void Client::listenForLoser(sf::Packet packet)
{
    CommonNetworking::PacketType type;
    int loserId;

    if (!(packet >> type >> loserId)) return;

    if (type != CommonNetworking::PacketType::LOSER) return;

    if (id == loserId) {
        std::cout << "You lost!" << std::endl;
    }
    else {
        std::cout << "You won!" << std::endl;
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

        std::cout << "Trying to connect to server " << sv_address << std::endl;

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

void Client::start(std::string ip, unsigned short port)
{
    hasStarted = true;
    socket.setBlocking(true);

    //std::string sv_addr_str;
    //std::cout << "Enter server address: " << std::endl;
    //std::cin >> sv_addr_str;

    //sv_address = sf::IpAddress(sv_addr_str);
    sv_address = sf::IpAddress(ip);

    //unsigned short port;
    //std::cout << "Enter client port: " << std::endl;
    //std::cin >> port;

    // bind the socket to a port
    if (socket.bind(port) != sf::Socket::Done)
    {
        std::cout << "ERROR BINDING TO SOCKET!" << std::endl;
        exit(1);
    }

    std::cout << "Socket binded successfully on port" << port << "!" << std::endl;

    connect();
    waitForMapInfo();
    socket.setBlocking(false);

    characters = &(Entities::getInstance().getCharacters());
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

        // smoothly move each character into his new position
        for (int i = 0; i < characters->size(); i++) {
            if (i != id) {
                ((*characters)[i])->slideToTargetPos(positionSmoothRate);
            }
        }
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
