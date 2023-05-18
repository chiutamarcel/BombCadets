#pragma once

#include <string>

class MapText {
	char** mapMatrix;
	int dimX, dimY;

public:
	MapText(int _dimX, int _dimY);
	MapText(const MapText& other);
	~MapText();

	void readFromFile(std::string filename);

	char** c_str() const;

	char& at(int x, int y);

	friend std::ostream& operator<<(std::ostream& out, const MapText& mapText);
};

std::ostream& operator<<(std::ostream& out, const MapText& mapText);