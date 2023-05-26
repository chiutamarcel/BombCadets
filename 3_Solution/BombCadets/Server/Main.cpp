#include "Server.h"

#include <iostream>

int main()
{
    Server &server = Server::getInstance();

    try
    {
        server.start();

        // Main loop
        while (true)
        {
            server.update();

        }

    }
    catch (std::string error)
    {
        std::cout << "ERR: " << error << std::endl;
    }

    server.deleteInstance();
}