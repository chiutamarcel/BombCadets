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
	targetPos = position;
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

void Character::setVelocity(sf::Vector2f vel)
{
	velocity = vel;
}

const sf::Vector2f& Character::getVelocity()
{
	return velocity;
}

sf::Vector2f Character::lerp(sf::Vector2f from, sf::Vector2f to, float rate)
{
	if (rate > 100) {
		throw std::string("Lerp rate cannot surpass 100!");
		exit(1);
	}

	sf::Vector2f result;

	result.x = from.x * (1 - (rate / 100)) + to.x * (rate / 100);
	result.y = from.y * (1 - (rate / 100)) + to.y * (rate / 100);

	return result;
}

void Character::slideTo(sf::Vector2f to, float rate)
{
	setPosition(lerp(getPosition(), to, rate));
}

void Character::slideToTargetPos(float rate)
{
	slideTo(targetPos, rate);
}

void Character::setTargetPos(sf::Vector2f _targetPos)
{
	targetPos = _targetPos;
}
