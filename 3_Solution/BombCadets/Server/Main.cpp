#include "Server.h"
#include "Logger.h"

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
		Logger::getInstance()->log(LogLevel::ERROR, error);
        std::cout << "ERR: " << error << std::endl;
    }

    server.deleteInstance();
}