#pragma once

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

class Client
{
	static int lastId;
	int id;
	sf::IpAddress ip;
	sf::Vector2f velocity;
	sf::UdpSocket* serverSocket;

	void updateVelocity();

public:
	Client(sf::UdpSocket* _serverSocket = nullptr);
	Client(std::string _ip, sf::UdpSocket* _serverSocket = nullptr);

	const sf::IpAddress& getIp();

	void setVelocity(sf::Vector2f vel);

	void update();
	void send(sf::Packet& packet);
};

