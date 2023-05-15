#include "Client.h"
#include "Client.h"
#include "Map.h"
#include "Common.h"

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

void Client::connect()
{
    sf::Packet packet;

    std::cout << "Trying to connect to server..." << std::endl;

    packet << CommonNetworking::PacketType::MESSAGE << "connect";

    send(packet);

    packet.clear();

    std::string text;

    packet = receivePacket();

    if (!packet) {
        throw "Server connection failed!";
    }

    packet >> text;

    if (strcmp(text.c_str(), "connected")) {
        throw text.c_str();
    }

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
        sf::Packet packet;

        packet = receivePacket();

        if (packet) {
            std::cout << packet << std::endl;
        }
    }
}

void Client::send(sf::Packet& packet)
{
    socket.send(packet, sv_address, SERVER_PORT);
}

sf::Packet&& Client::receivePacket()
{
    sf::Packet packet;
    sf::IpAddress sender_addr;
    unsigned short sender_port;

    socket.receive(packet, sender_addr, sender_port);

    if (sender_addr != sv_address.toString() || sender_port != SERVER_PORT) {
        return std::move(sf::Packet());
    }

    return std::move(packet);
}

