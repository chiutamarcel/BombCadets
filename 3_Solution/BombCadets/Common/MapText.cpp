#include "MapText.h"

#include <fstream>
#include <iostream>

MapText::MapText(int _dimX, int _dimY)
{
	dimX = _dimX;
	dimY = _dimY;

	mapMatrix = new char* [dimY];
	for (int i = 0; i < dimY; i++)
	{
		mapMatrix[i] = new char[dimX + 1];

		for (int j = 0; j < dimX; j++) {
			mapMatrix[i][j] = ' ';
		}

		mapMatrix[i][dimX] = '\0';
	}
}

MapText::MapText(const MapText& other):
	MapText(other.dimX, other.dimY)
{
	for (int i = 0; i < dimY; i++) {
		for (int j = 0; j < dimX + 1; j++) {
			mapMatrix[i][j] = other.mapMatrix[i][j];
		}
	}
}

MapText::~MapText()
{
	for (int i = 0; i < (int)(dimY); i++)
	{
		delete[] mapMatrix[i];
	}
	delete[] mapMatrix;
}

void MapText::readFromFile(std::string filename)
{
	try {
		std::ifstream map(filename);

		if (!map)
			throw std::string("Error while reading map file!");

		for (int i = 0; i < dimY; i++) {
			for (int j = 0; j < dimX; j++) {
				map.get(mapMatrix[i][j]);
			}
			map.ignore(1, '\n');
		}

		map.close();
	}
	catch (std::string e) {
		std::cout << e;
		exit(1);
	}
}

void MapText::putBreakableBlocks(int brkBlkCount) {
	int count = 0;
	std::vector<std::pair<int, int>> emptySpace;
	
	for (int i = 0; i < dimY; i++)
		for (int j = 0; j < dimX; j++)
		{
			if (mapMatrix[i][j] == '0')
				emptySpace.push_back(std::make_pair(i, j));
			count++;
		}
	
	while (brkBlkCount)
	{
		srand(time(NULL));
	
		if (emptySpace.size() == 0) break;
	
		int index = rand() % emptySpace.size();
		int x = emptySpace[index].first;
		int y = emptySpace[index].second;
	
		mapMatrix[x][y] = '2';
		emptySpace.erase(emptySpace.begin() + index);
		brkBlkCount--;
	}
}

char** MapText::c_str() const
{
	return mapMatrix;
}

char& MapText::at(int x, int y)
{
	try {
		if (x >= 0 || x <= dimX)
			throw std::string("index out of range");
		if (y >= 0 || y <= dimY)
			throw std::string("index out of range");

		return mapMatrix[x][y];
	}
	catch (std::string e) {
		std::cout << e;
		exit(1);
	}
}

std::ostream& operator<<(std::ostream& out, const MapText& mapText) {
	for (int i = 0; i < mapText.dimY; i++) {
		for (int j = 0; j < mapText.dimX; j++) {
			out << mapText.mapMatrix[i][j];
		}
		out << std::endl;
	}
	out << std::endl;
	return out;
}

std::istream& operator>>(std::istream& in, MapText& mapText) {
	for (int i = 0; i < mapText.dimY; i++) {
		for (int j = 0; j < mapText.dimX; j++) {
			in.get(mapText.mapMatrix[i][j]);
		}
		in.ignore(1, '\n');
	}

	return in;
}


sf::Packet& operator<<(sf::Packet& packet, const MapText& mapText) {
	for (int i = 0; i < mapText.dimY; i++) {
		packet << mapText.mapMatrix[i];
	}
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, MapText& mapText) {
	for (int i = 0; i < mapText.dimY; i++) {
		packet >> mapText.mapMatrix[i];
	}
	return packet;
}