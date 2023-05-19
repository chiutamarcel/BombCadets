#include "Common.h"
#include "GameConfig.h"

namespace CommonNetworking {
	sf::Packet& operator>>(sf::Packet& packet, PacketType& packetType) {
		unsigned int type;
		packet >> type;
		packetType = static_cast<PacketType>(type);

		return packet;
	}
}

namespace Map {
	void writeBreakableBlocks(MapText& mapText) {
		using namespace GameConfig;

		int count = 0;
		std::vector<std::pair<int, int>> emptySpace;

		for (int i = 0; i < BLOCKSONSCREENY; i++)
			for (int j = 0; j < BLOCKSONSCREENX; j++)
			{
				if (mapText.at(i, j) == '0')
					emptySpace.push_back(std::make_pair(i, j));
				count++;
			}

		int numberOfBreakableWalls = NRBREAKABLEWALLS;
		while (numberOfBreakableWalls)
		{
			srand(time(NULL));

			if (emptySpace.size() == 0) break;

			int index = rand() % emptySpace.size();
			int x = emptySpace[index].first;
			int y = emptySpace[index].second;

			mapText.at(x, y) = '2';
			emptySpace.erase(emptySpace.begin() + index);
			numberOfBreakableWalls--;
		}
	}
}