#pragma once
#include "Character.h"
class Player : public Character
{
	sf::Clock cooldownTimer;
	sf::Vector2f input;

	void movement(float deltaTime);
	void init();

	Player(sf::Vector2f position, sf::Vector2f size, float speed = 0);
public:
	Player(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, float speed = 0);
	Player(sf::Vector2f position, float length, sf::Texture* texture, float speed = 0);
	Player(sf::Vector2f position, sf::Vector2f size, sf::Color color, float speed = 0);
	Player(sf::Vector2f position, float length, sf::Color color, float speed = 0);
	~Player();

	virtual void update(float deltaTime) override;
	virtual void pollEvents() override;
};

