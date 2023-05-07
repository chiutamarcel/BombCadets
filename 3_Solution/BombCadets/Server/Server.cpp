#include <iostream>
#include "SFML/Network.hpp"

#define CLIENT_PORT 54001
#define SERVER_PORT 54000

int main()
{

    try
    {
        sf::UdpSocket socket;

        std::cout << "Binding socket.." << std::endl;

        // Binding socket
        if(socket.bind(SERVER_PORT) != sf::Socket::Done)
        {
            throw std::string("Could not bind socket!");
        }

        std::cout << "Socket bound successfully on port " << SERVER_PORT << std::endl;

        //  Receiving data
        char indata[100];
        std::size_t received;

        sf::IpAddress sender("127.0.0.1");
        unsigned short port = CLIENT_PORT;

        while (true)
        {
            if (socket.receive(indata, 100, received, sender, port) != sf::Socket::Done)
            {
                throw std::string("Could not receive data from port ") + std::string(std::to_string(CLIENT_PORT));
            }
            std::cout << "Received " << received << " bytes from " << sender << " on port " << port << std::endl;
            std::cout << indata << std::endl;

            if (strcmp(indata, "connect") == 0)
            {
                char outdata[100] = "connected";
                socket.send(outdata, 100, sender, port) != sf::Socket::Done;
            }

        }

    }
    catch (std::string error)
    {
        std::cout << error << std::endl;
    }
}