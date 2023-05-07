#include "Server.h"

#include <iostream>

int main()
{
    Server server;

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
        std::cout << error << std::endl;
    }
}