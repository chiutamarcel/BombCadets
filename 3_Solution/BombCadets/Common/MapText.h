#pragma once

#include <string>

#include "SFML/Network.hpp"

class MapText {
	char** mapMatrix;
	int dimX, dimY;

public:
	MapText(int _dimX, int _dimY);
	MapText(const MapText& other);
	~MapText();

	void readFromFile(std::string filename);
	void putBreakableBlocks(int brkBlkCount);

	char** c_str() const;

	char& at(int x, int y);

	std::string toString();

	friend std::ostream& operator<<(std::ostream& out, const MapText& mapText);
	friend std::istream& operator>>(std::istream& in, MapText& mapText);
	friend sf::Packet& operator<<(sf::Packet& packet, const MapText& mapText);
	friend sf::Packet& operator>>(sf::Packet& packet, MapText& mapText);
};

std::ostream& operator<<(std::ostream& out, const MapText& mapText);
std::istream& operator>>(std::ostream& in, MapText& mapText);

sf::Packet& operator<<(sf::Packet& packet, const MapText& mapText);
sf::Packet& operator>>(sf::Packet& packet, MapText& mapText);