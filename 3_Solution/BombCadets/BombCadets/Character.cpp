#include "Character.h"
#include "Entities.h"
#include "Bomb.h"
#include <iostream>

Character::Character
(
	sf::Vector2f position, 
	sf::Vector2f size, 
	float _speed
) :
	Entity(position, size)
{
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
	shape.setScale(0.9f, 0.9f);
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
	shape.setScale(0.9f, 0.9f);
}

Character::~Character()
{
}

void Character::update(float deltaTime)
{
	Entity::update(deltaTime);

	sf::Vector2f temp(velocity.x, 0.0f);
	checkCollision(temp);
	velocity.x = temp.x;
	temp = sf::Vector2f(0.0f, velocity.y);
	checkCollision(temp);
	velocity.y = temp.y;
	
	shape.move(velocity);
}

void Character::die()
{

}

void Character::checkCollision(sf::Vector2f &velocity)
{
	Character player = *this;
	player.shape.move(velocity);

	for (auto entity : Entities::getInstance().getBreakableBlocks())
	{
		Bomb* b = dynamic_cast<Bomb*>(entity);
		if (player.getShape().getGlobalBounds().intersects(entity->getShape().getGlobalBounds()))
		{
			velocity = sf::Vector2f(0.f, 0.f);
			return;
		}
	}
	for (auto entity : Entities::getInstance().getWalls())
	{
		if (player.getShape().getGlobalBounds().intersects(entity->getShape().getGlobalBounds()))
		{
			velocity = sf::Vector2f(0.f, 0.f);
			return;
		}
	}
}
