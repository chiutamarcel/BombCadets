#pragma once
#include "WorldObject.h"
#include <SFML/Audio.hpp>

class Bomb :
    public WorldObject
{
public:
	Bomb(sf::Vector2f position, sf::Vector2f size);
	Bomb(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture);
	Bomb(sf::Vector2f position, float length, sf::Texture* texture);
	Bomb(sf::Vector2f position, sf::Vector2f size, sf::Color color);
	Bomb(sf::Vector2f position, float length, sf::Color color);

	virtual void update(float deltaTime);
	void explode();
	sf::Vector2f getPositionExplosion();

	virtual ~Bomb();
private:
	sf::Clock planted;
	sf::Texture* bombTexture = new sf::Texture();
	sf::Texture* explosionTexture = new sf::Texture();
};

