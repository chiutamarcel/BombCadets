#pragma once
#include "Block.h"
class BreakableBlock :
    public Block
{
public:
	BreakableBlock(sf::Vector2f position, sf::Vector2f size);
	BreakableBlock(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture);
	BreakableBlock(sf::Vector2f position, float length, sf::Texture* texture);
	BreakableBlock(sf::Vector2f position, sf::Vector2f size, sf::Color color);
	BreakableBlock(sf::Vector2f position, float length, sf::Color color);
	virtual ~BreakableBlock();

	//virtual void die();
};

