#define CLIENT_PORT 54001
#define SERVER_PORT 54000
#define MAX_CLIENTS 4

#define PACKETDATASIZE 100

namespace CommonNetworking {
	enum PacketType {
		VELOCITY,
		MESSAGE
	};
}