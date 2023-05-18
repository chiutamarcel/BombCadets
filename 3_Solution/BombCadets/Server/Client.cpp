#include "Client.h"
#include "Client.h"
#include "Common.h"

const sf::IpAddress& Client::getIp()
{
	return ip;
}

void Client::setVelocity(sf::Vector2f vel)
{
	velocity = vel;
}

Client::Client(int _id, sf::UdpSocket* _serverSocket) {
	velocity = sf::Vector2f(0.0f, 0.0f);
	serverSocket = _serverSocket;
	id = _id;
}

Client::Client(int _id, std::string _ip, sf::UdpSocket* _serverSocket)
	: Client(id, _serverSocket)
{
	ip = sf::IpAddress(_ip);
}

void Client::send(sf::Packet& packet)
{
	serverSocket->send(packet, ip, CLIENT_PORT);
}

void Client::updateVelocity() {
	sf::Packet packet;
	packet << CommonNetworking::PacketType::VELOCITY << id << velocity.x << velocity.y;
	send(packet);
}

void Client::update() {
	//updateVelocity();
}
