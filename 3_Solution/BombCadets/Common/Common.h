#define CLIENT_PORT 54001
#define SERVER_PORT 54000
#define MAX_CLIENTS 4

#define PACKETDATASIZE 100

#include "SFML/Network.hpp"

namespace CommonNetworking {
	enum PacketType {
		VELOCITY,
		MESSAGE
	};

	extern sf::Packet& operator>>(sf::Packet& packet, PacketType& packetType);
}

namespace Map {
	void writeBreakableBlocks(char** mapMatrix);
}