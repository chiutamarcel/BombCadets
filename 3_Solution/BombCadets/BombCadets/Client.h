#pragma once

#include "SFML/Network.hpp"

class Client
{
	static Client* instance;

	sf::UdpSocket socket;
	sf::IpAddress sv_address;
	bool hasStarted;

	~Client();
	Client();
	Client(Client& other) = delete;

	void chatPrompt();

public:
	void start();
	void update();

	void connect();
	void disconnect();

	static Client& getInstance();
	static void deleteInstance();

	const bool& getHasStarted();

	void send(sf::Packet& packet);
	sf::Packet receivePacket();
};

