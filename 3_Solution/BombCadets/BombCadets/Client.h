#pragma once

#include "SFML/Network.hpp"
#include "Common.h"

class Client
{
	int id;
	static Client* instance;

	sf::UdpSocket socket;
	sf::IpAddress sv_address;
	bool hasStarted;

	~Client();
	Client();
	Client(Client& other) = delete;

	void chatPrompt();
	void syncVelocities(sf::Packet packet);
	void sendLocalVelocity();

	void sendPackets();
	void receivePackets();
	
	MapText waitForMapInfo();

public:
	void start();
	void update();
	void pollEvents();

	void connect();
	void disconnect();

	static Client& getInstance();
	static void deleteInstance();

	const bool& getHasStarted();

	void send(sf::Packet& packet);
	void receivePacket(sf::Packet& packet);

	const int& getId();
	void setId(int _id);
};

