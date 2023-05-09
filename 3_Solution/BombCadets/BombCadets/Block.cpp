#include "Block.h"

Block::Block(sf::Vector2f position, sf::Vector2f size) :
	WorldObject(position, size)
{
}

Block::Block(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture) :
	WorldObject(position, size, texture)
{
}

Block::Block(sf::Vector2f position, float length, sf::Texture* texture) :
	WorldObject(position, length, texture)
{
}

Block::Block(sf::Vector2f position, sf::Vector2f size, sf::Color color) :
	WorldObject(position, size, color)
{
}

Block::Block(sf::Vector2f position, float length, sf::Color color) :
	WorldObject(position, length, color)
{
}

Block::~Block()
{
}

