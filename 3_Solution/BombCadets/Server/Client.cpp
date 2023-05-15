#include "Client.h"
#include "Client.h"
#include "Common.h"

int Client::lastId = 0;

const sf::IpAddress& Client::getIp()
{
	return ip;
}

void Client::setVelocity(sf::Vector2f vel)
{
	velocity = vel;
}

Client::Client(sf::UdpSocket* _serverSocket) {
	velocity = sf::Vector2f(0.0f, 0.0f);
	id = lastId + 1;
	serverSocket = _serverSocket;
}

Client::Client(std::string _ip, sf::UdpSocket* _serverSocket)
	: Client(_serverSocket)
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
	updateVelocity();
}
