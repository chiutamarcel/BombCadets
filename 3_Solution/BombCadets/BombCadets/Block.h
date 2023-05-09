#pragma once
#include "WorldObject.h"
class Block :
    public WorldObject
{
public:
	Block(sf::Vector2f position, sf::Vector2f size);
	Block(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture);
	Block(sf::Vector2f position, float length, sf::Texture* texture);
	Block(sf::Vector2f position, sf::Vector2f size, sf::Color color);
	Block(sf::Vector2f position, float length, sf::Color color);
	virtual ~Block();
};

