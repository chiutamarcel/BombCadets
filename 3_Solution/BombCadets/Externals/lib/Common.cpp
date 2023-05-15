#include "Common.h"

namespace CommonNetworking {
	sf::Packet& operator>>(sf::Packet& packet, PacketType& packetType) {
		unsigned int type;
		packet >> type;
		packetType = type;

		return packet;
	}
}