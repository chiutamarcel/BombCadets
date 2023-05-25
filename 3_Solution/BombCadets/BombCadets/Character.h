#pragma once
#include "Entity.h"

class Character : public Entity
{
protected:
	float speed;
	sf::Vector2f velocity;
	sf::Vector2f targetPos;

public:
	Character(sf::Vector2f position, sf::Vector2f size, float _speed = 0);
	Character(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, float _speed = 0);
	Character(sf::Vector2f position, float length, sf::Texture* texture, float _speed = 0);
	Character(sf::Vector2f position, sf::Vector2f size, sf::Color color, float _speed = 0);
	Character(sf::Vector2f position, float length, sf::Color color, float _speed = 0);
	~Character();

	virtual void update(float deltaTime) override;
	virtual void die();
	
	void checkCollision(sf::Vector2f& velocity);

	sf::Vector2f lerp(sf::Vector2f from, sf::Vector2f to, float rate);

	void slideTo(sf::Vector2f to, float rate);
	void slideToTargetPos(float rate);

	// getters and setters
	void setVelocity(sf::Vector2f vel);
	const sf::Vector2f& getVelocity();

	void setTargetPos(sf::Vector2f _targetPos);
};

