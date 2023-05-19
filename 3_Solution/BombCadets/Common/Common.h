#define CLIENT_PORT 54001
#define SERVER_PORT 54000
#define MAX_CLIENTS 4

#define PACKETDATASIZE 100

#include "SFML/Network.hpp"
#include "MapText.h"

namespace CommonNetworking {
	enum PacketType {
		VELOCITY,
		MESSAGE,
		MAPINFO
	};

	extern sf::Packet& operator>>(sf::Packet& packet, PacketType& packetType);
}

namespace Map {
	void writeBreakableBlocks(MapText& mapText);
}