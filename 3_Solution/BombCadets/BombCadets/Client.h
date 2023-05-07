#pragma once

#include "SFML/Network.hpp"

class Client
{
	sf::UdpSocket socket;
	sf::IpAddress sv_address;

	void connect();

public:
	void start();
	void update();
};

