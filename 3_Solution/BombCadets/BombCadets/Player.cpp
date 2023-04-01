#include "Player.h"

void Player::movement(float deltaTime)
{
	input.y = sf::Keyboard::isKeyPressed(sf::Keyboard::S) -
		sf::Keyboard::isKeyPressed(sf::Keyboard::W);

	input.x = sf::Keyboard::isKeyPressed(sf::Keyboard::D) -
		sf::Keyboard::isKeyPressed(sf::Keyboard::A);

	velocity = input * speed * deltaTime;
}

Player::Player(sf::Vector2f position, sf::Vector2f size, float speed) :
	Character(position, size, speed)
{
}

Player::Player(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, float speed):
	Character(position, size, texture, speed)
{
}

Player::Player(sf::Vector2f position, float length, sf::Texture* texture, float speed):
	Character(position, length, texture, speed)
{
}

Player::Player(sf::Vector2f position, sf::Vector2f size, sf::Color color, float speed):
	Character(position, size, color, speed)
{
}

Player::Player(sf::Vector2f position, float length, sf::Color color, float speed):
	Character(position, length, color, speed)
{
}

Player::~Player()
{
}

void Player::update(float deltaTime)
{
	Character::update(deltaTime);

	movement(deltaTime);
}
