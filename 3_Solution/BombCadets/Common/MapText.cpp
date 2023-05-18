#include "MapText.h"

#include <fstream>

MapText::MapText(int _dimX, int _dimY)
{
	dimX = _dimX;
	dimY = _dimY;

	mapMatrix = new char* [dimY];
	for (int i = 0; i < dimY; i++)
	{
		mapMatrix[i] = new char[dimX];
	}
}

MapText::MapText(const MapText& other):
	MapText(other.dimX, other.dimY)
{
	for (int i = 0; i < dimY; i++) {
		for (int j = 0; j < dimX; j++) {
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

		if (!map) exit(1); // TODO: throw exception

		for (int i = 0; i < dimY; i++) {
			for (int j = 0; j < dimX; j++) {
				map.get(mapMatrix[i][j]);
			}
			map.ignore(1, '\n');
		}

		map.close();
	}
	catch (...) {
		// TODO: add this
	}
}

char** MapText::c_str() const
{
	return mapMatrix;
}

char& MapText::at(int x, int y)
{
	return mapMatrix[x][y];
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
