#include "Client.h"
#include "Server.h"
#include <iostream>

const sf::IpAddress& Client::getIp() const
{
	return ip;
}

const unsigned short& Client::getPort() const
{
	return port;
}

void Client::confirmConnection() {
	sf::Packet packet;
	packet << CommonNetworking::PacketType::MESSAGE << "connected" << id;
	send(packet);
}

void Client::sendMapInfo(const MapText& mapText)
{
	sf::Packet packet;

	packet << CommonNetworking::PacketType::MAPINFO << mapText;

	send(packet);

}

Client::Client(int _id, unsigned short _port, sf::UdpSocket* _serverSocket) {
	serverSocket = _serverSocket;
	id = _id;
	port = _port;
	
	isDead = false;
	for (int i = 0; i < MAX_CLIENTS; i++) {
		killVotes[i] = 0;
	}
}

Client::Client(int _id, unsigned short _port, std::string _ip, sf::UdpSocket* _serverSocket)
	: Client(_id, _port, _serverSocket)
{
	ip = sf::IpAddress(_ip);
}

void Client::send(sf::Packet& packet)
{
	serverSocket->send(packet, ip, port);
}

void Client::die()
{
	std::cout << "Client " << id << " died!" << std::endl;
	sf::Packet packet;

	send(packet);
	Server::getInstance().endGame(id);
}

void Client::getKillVoted(int voterId, int playerCount)
{
	if (isDead) return;

	if (voterId < 0 || voterId >= playerCount) {
		throw std::string("id out of range!");
	}

	killVotes[voterId] = 1;

	int getKilled = 1;
	for (int i = 0; i < playerCount; i++) {
		if (killVotes[i] == 0) {
			getKilled = 0;
			break;
		}
	}

	if (getKilled) {
		die();
	}
}

void Client::update() {
	
}
