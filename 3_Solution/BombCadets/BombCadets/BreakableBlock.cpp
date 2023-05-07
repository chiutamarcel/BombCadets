#include "BreakableBlock.h"

BreakableBlock::BreakableBlock(sf::Vector2f position, sf::Vector2f size) :
	Block(position, size){}

BreakableBlock::BreakableBlock(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture) :
	Block(position, size, texture){}

BreakableBlock::BreakableBlock(sf::Vector2f position, float length, sf::Texture* texture) :
	Block(position, length, texture){}

BreakableBlock::BreakableBlock(sf::Vector2f position, sf::Vector2f size, sf::Color color) :
	Block(position, size, color) {}

BreakableBlock::BreakableBlock(sf::Vector2f position, float length, sf::Color color) :
	Block(position, length, color) {}

BreakableBlock::~BreakableBlock() {}