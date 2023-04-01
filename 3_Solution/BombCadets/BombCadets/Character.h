#pragma once
#include "Entity.h"
class Character : public Entity
{
protected:
	float speed;
	sf::Vector2f velocity;


	Character(sf::Vector2f position, sf::Vector2f size, float _speed = 0);
public:
	Character(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, float _speed = 0);
	Character(sf::Vector2f position, float length, sf::Texture* texture, float _speed = 0);
	Character(sf::Vector2f position, sf::Vector2f size, sf::Color color, float _speed = 0);
	Character(sf::Vector2f position, float length, sf::Color color, float _speed = 0);
	virtual ~Character();

	virtual void update(float deltaTime) override;
	virtual void die();
};

