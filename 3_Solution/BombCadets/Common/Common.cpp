#include "Common.h"

namespace CommonNetworking {
	sf::Packet& operator>>(sf::Packet& packet, PacketType& packetType) {
		unsigned int type;
		packet >> type;
		packetType = static_cast<PacketType>(type);

		return packet;
	}
}