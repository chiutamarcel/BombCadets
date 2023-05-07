#pragma once
#include "WorldObject.h"
class Explosion :
    public WorldObject
{
public:
	Explosion(sf::Vector2f position, sf::Vector2f size);
	Explosion(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture);
	Explosion(sf::Vector2f position, float length, sf::Texture* texture);
	Explosion(sf::Vector2f position, sf::Vector2f size, sf::Color color);
	Explosion(sf::Vector2f position, float length, sf::Color color);

	virtual void update(float deltaTime);
	
	sf::Vector2f getScale();
	void setScale(float x, float y);
	void removeExplosion();

	void checkCollision();

	virtual ~Explosion();
	
private:
	bool growing = true;
	bool alive = true;
};

