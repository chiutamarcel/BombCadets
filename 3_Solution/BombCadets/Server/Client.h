#pragma once

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "MapText.h"

class Client
{
	int id;
	sf::IpAddress ip;
	sf::UdpSocket* serverSocket;

public:
	Client(int _id, sf::UdpSocket* _serverSocket = nullptr);
	Client(int _id, std::string _ip, sf::UdpSocket* _serverSocket = nullptr);

	const sf::IpAddress& getIp();

	void confirmConnection();
	void sendMapInfo(const MapText& mapText);
	void update();
	void send(sf::Packet& packet);
};

