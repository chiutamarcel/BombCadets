#pragma once

#include "SFML/Network.hpp"
#include "Common.h"
#include "Character.h"

class Client
{
	int id;
	static Client* instance;

	sf::UdpSocket socket;
	sf::IpAddress sv_address;
	bool hasStarted;

	sf::Clock lastPositionTimer;

	std::vector<Character*> *characters;

	~Client();
	Client();
	Client(Client& other) = delete;

	void chatPrompt();
	//void syncVelocities(sf::Packet packet);
	void syncPositions(sf::Packet packet);
	void sendLocalVelocity();
	void sendLocalPosition();
	
	void sendPackets();
	void receivePackets();
	void listenForBombPacket(sf::Packet packet);
	void listenForLoser(sf::Packet packet);
	
	MapText waitForMapInfo();

public:
	void start(std::string ip, unsigned short port);
	void update();
	void pollEvents();

	void sendBombPacket(sf::Vector2f bombPos);
	void sendKillRequest(int targetId);

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

