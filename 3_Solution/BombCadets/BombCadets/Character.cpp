#include "Character.h"
#include <iostream>

Character::Character
(
	sf::Vector2f position, 
	sf::Vector2f size, 
	float _speed
) :
	Entity(position, size)
{
	input = sf::Vector2f(0.0f, 0.0f);
	velocity = sf::Vector2f(0.0f, 0.0f);
	speed = _speed;
}

Character::Character
(
	sf::Vector2f position, 
	sf::Vector2f size, 
	sf::Texture* texture, 
	float _speed
) :
	Character(position, size, _speed)
{
	shape.setTexture(texture);
}

Character::Character
(
	sf::Vector2f position, 
	float length, 
	sf::Texture* texture, 
	float _speed
) :
	Character(
		position, 
		sf::Vector2f(length, length),
		texture,
		_speed)
{
}

Character::Character
(
	sf::Vector2f position, 
	sf::Vector2f size, 
	sf::Color color, 
	float _speed
) : 
	Character(position, size, _speed)
{
	speed = _speed;
}

Character::Character
(
	sf::Vector2f position, 
	float length, 
	sf::Color color, 
	float _speed
) :
	Character(position, sf::Vector2f(length, length), _speed)
{
	shape.setFillColor(color);
}

Character::~Character()
{
}

void Character::update(float deltaTime)
{
	Entity::update(deltaTime);

	input.y =	sf::Keyboard::isKeyPressed(sf::Keyboard::S) -
				sf::Keyboard::isKeyPressed(sf::Keyboard::W);

	input.x =	sf::Keyboard::isKeyPressed(sf::Keyboard::D) -
				sf::Keyboard::isKeyPressed(sf::Keyboard::A);

	velocity = input * speed * deltaTime;

	shape.move(velocity);
}

void Character::die()
{

}
