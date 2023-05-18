#include "Client.h"
#include "Client.h"
#include "Map.h"
#include "Common.h"
#include "Entities.h"

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
    int id;
    sf::Vector2f vel;

    if (!(packet >> type >> id >> vel.x >> vel.y)) return;

    if (type != CommonNetworking::PacketType::VELOCITY) return;

    const std::vector<Character*>& characters = Entities::getInstance().getCharacters();

    //if (id <= 0 || id >= characters.size())
    //    throw "id out of bounds!";

    characters[id]->setVelocity(vel);

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
    sf::Packet packet;

    packet = receivePacket();

    syncVelocities(packet);
}

void Client::connect()
{
    sf::Packet packet;

    std::cout << "Trying to connect to server..." << std::endl;

    packet << CommonNetworking::PacketType::MESSAGE << "connect";

    send(packet);

    packet.clear();

    std::string text;
    CommonNetworking::PacketType type;
    int _id;

    packet = receivePacket();

    if (!(packet >> type >> text >> _id)) {
        throw "Server connection failed!";
    }

    if (!type == CommonNetworking::PacketType::MESSAGE) {
        return;
    }

    if (strcmp(text.c_str(), "connected")) {
        throw text.c_str();
    }

    id = _id;

    std::cout << "Server connection successful!" << std::endl;
    Map::readFromFile("map.txt");
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
    socket.setBlocking(false);
}

void Client::update()
{
    if (hasStarted == true) {
        receivePackets();
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

sf::Packet Client::receivePacket()
{
    sf::Packet packet;
    sf::IpAddress sender_addr;
    unsigned short sender_port;

    socket.receive(packet, sender_addr, sender_port);

    if (sender_addr != sv_address.toString() || sender_port != SERVER_PORT) {
        return sf::Packet();
    }

    return packet;
}

const int& Client::getId()
{
    return id;
}

void Client::setId(int _id)
{
    id = _id;
}
