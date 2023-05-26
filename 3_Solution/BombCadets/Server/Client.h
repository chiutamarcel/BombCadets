#pragma once

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "MapText.h"
#include "Common.h"

class Client
{
	int id;
	sf::IpAddress ip;
	unsigned short port;
	sf::UdpSocket* serverSocket;
	int killVotes[MAX_CLIENTS];
	bool isDead;

public:
	Client(int _id, unsigned short _port, sf::UdpSocket* _serverSocket = nullptr);
	Client(int _id, unsigned short _port, std::string _ip, sf::UdpSocket* _serverSocket = nullptr);
	
	const sf::IpAddress& getIp() const;
	const unsigned short& getPort() const;

	void confirmConnection();
	void sendMapInfo(const MapText& mapText);
	void update();
	void send(sf::Packet& packet);
	void die();

	void getKillVoted(int voterId, int playerCount);
};

