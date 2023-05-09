#pragma once
#include "Entity.h"
class WorldObject :
    public Entity
{
public:
	WorldObject(sf::Vector2f position, sf::Vector2f size);
	WorldObject(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture);
	WorldObject(sf::Vector2f position, float length, sf::Texture* texture);
	WorldObject(sf::Vector2f position, sf::Vector2f size, sf::Color color);
	WorldObject(sf::Vector2f position, float length, sf::Color color);
	virtual ~WorldObject(){}
};

