#pragma once
#include "Entity.h"
class Character : public Entity
{
	sf::Vector2f velocity;
	sf::Vector2f input;
	float speed;
	sf::Clock planted;

	Character(sf::Vector2f position, sf::Vector2f size, float _speed = 0);
public:
	Character(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, float _speed = 0);
	Character(sf::Vector2f position, float length, sf::Texture* texture, float _speed = 0);
	Character(sf::Vector2f position, sf::Vector2f size, sf::Color color, float _speed = 0);
	Character(sf::Vector2f position, float length, sf::Color color, float _speed = 0);
	~Character();

	virtual void update(float deltaTime);
	virtual void die();
	
	void checkCollision(sf::Vector2f& velocity);
};

