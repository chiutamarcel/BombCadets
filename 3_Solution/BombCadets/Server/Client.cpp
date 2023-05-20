#include "Client.h"
#include "Common.h"

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

void Client::update() {
	
}
