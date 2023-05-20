#include "Player.h"

#include "Entities.h"

void Player::movement(float deltaTime)
{
	velocity = input * speed * deltaTime;
}

void Player::init()
{
	Entities::getInstance().setPlayer(*this);
	planted.restart();
	input = sf::Vector2f(0.0f, 0.0f);
}

Player::Player(sf::Vector2f position, sf::Vector2f size, float speed):
	Character(position, size, speed)
{
	init();
}

Player::Player(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, float speed):
	Character(position, size, texture, speed)
{
	init();
}

Player::Player(sf::Vector2f position, float length, sf::Texture* texture, float speed):
	Character(position, length, texture, speed)
{
	init();
}

Player::Player(sf::Vector2f position, sf::Vector2f size, sf::Color color, float speed):
	Character(position, size, color, speed)
{
	init();
}

Player::Player(sf::Vector2f position, float length, sf::Color color, float speed):
	Character(position, length, color, speed)
{
	init();
}

Player::~Player()
{
}

void Player::update(float deltaTime)
{
	Character::update(deltaTime);

	movement(deltaTime);
}

void Player::pollEvents()
{
	// Movement input
	input.y = sf::Keyboard::isKeyPressed(sf::Keyboard::S) -
		sf::Keyboard::isKeyPressed(sf::Keyboard::W);

	input.x = sf::Keyboard::isKeyPressed(sf::Keyboard::D) -
		sf::Keyboard::isKeyPressed(sf::Keyboard::A);

	//	Bomb plant
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) && (this->planted.getElapsedTime().asSeconds() > 3.f))
	{
		Entities::getInstance().getBombs().push_back(new Bomb(this->getShape().getPosition() + sf::Vector2f(16.f, 16.f), 32.f, sf::Color::Magenta));
		if (this->planted.getElapsedTime().asSeconds() >= 3)
			this->planted.restart();
	}
}
