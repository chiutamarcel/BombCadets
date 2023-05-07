#pragma once

#include <unordered_set>
#include <string>

#include "SFML/Network.hpp"

class Server
{
	sf::UdpSocket socket;
	std::unordered_set<std::string> connected_clients;

	sf::IpAddress sv_address;

	void listenForConnections(const char indata[100], sf::IpAddress sender);
	void spawnPlayer(std::string player_ip);
public:
	void start();
	void update();
};

