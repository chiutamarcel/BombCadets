#include "Client.h"
#include "Client.h"
#include "Map.h"
#include "Common/Common.h"

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
    char outdata[PACKETDATASIZE] = "connect";
    char indata[PACKETDATASIZE] = "";
    std::size_t received;
    

    sf::Packet inPacket;
    sf::IpAddress sender;
    unsigned short port;

    std::cout << "Trying to connect to server..." << std::endl;

    if (socket.send(outdata, PACKETDATASIZE, sv_address, SERVER_PORT) != sf::Socket::Done)
    {
        std::cout << "ERROR!" << std::endl;
        exit(1);
    }

    std::string text;
    if (socket.receive(inPacket, sender, port)) {
        if (port == SERVER_PORT) {
            inPacket >> text;
        }
    }

    if (port == SERVER_PORT) {

        if (!strcmp(text.c_str(), "connected")) {
            std::cout << "Server connection failed!" << std::endl;
            exit(1);
        }
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
        char indata[PACKETDATASIZE];
        std::size_t received;
        unsigned short port;

        sf::Socket::Status status;

        status = socket.receive(indata, PACKETDATASIZE, received, sv_address, port);
        
        if (status == sf::Socket::Done)
        {
            std::cout << indata << std::endl;
        }
        //chatPrompt();
    }
}
