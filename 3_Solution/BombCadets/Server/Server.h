#pragma once

#include <unordered_set>
#include <string>

#include "SFML/Network.hpp"

#include "Client.h"

#include "MapText.h"

class Server
{
	sf::UdpSocket socket;
	std::vector<Client*> connected_clients;
	sf::IpAddress sv_address;
	MapText mapText;

	void listenForConnections(sf::Packet packet, sf::IpAddress sender);
	void listenForPositions(sf::Packet packet, sf::IpAddress sender);
	Client* spawnPlayer(std::string player_ip);
	Client* searchClientByIp(std::string player_ip);
public:
	Server();

	void start();
	void update();
};

