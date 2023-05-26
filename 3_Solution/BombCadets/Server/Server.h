#pragma once

#include <unordered_set>
#include <string>

#include "SFML/Network.hpp"

#include "Client.h"

#include "MapText.h"

class Server
{
	static Server* instance;

	bool hasGameStarted;

	sf::UdpSocket socket;
	std::vector<Client*> connected_clients;
	sf::IpAddress sv_address;
	MapText mapText;

	void listenForConnections(sf::Packet packet, sf::IpAddress sender, unsigned short port);
	void listenForKillRequests(sf::Packet packet, sf::IpAddress sender, unsigned short port);
	//void listenForPositions(sf::Packet packet, sf::IpAddress sender, unsigned short port);
	//void listenForBombs(sf::Packet packet, sf::IpAddress sender, unsigned short port);
	void forwardPackets(sf::Packet packet, sf::IpAddress sender, unsigned short port);
	Client* spawnPlayer(std::string player_ip, unsigned short port);
	//Client* searchClientByIp(std::string player_ip);
	bool alreadyExists(std::string player_ip, unsigned short port);

	Server();
	~Server();
public:
	void endGame(int loserId);

	void start();
	void update();

	int getPlayerCount();

	static Server& getInstance();
	static void deleteInstance();

	const bool& getHasMatchStarted() const;
};

