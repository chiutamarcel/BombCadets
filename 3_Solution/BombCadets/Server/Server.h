#pragma once

#include <unordered_set>
#include <string>

#include "SFML/Network.hpp"

class Server
{
	sf::UdpSocket socket;
	std::unordered_set<std::string> connected_clients;

	sf::IpAddress sv_address;
	//unsigned short client_port;

	void listenForConnections(const char indata[100], sf::IpAddress sender);
public:
	void start();
	void update();
};

