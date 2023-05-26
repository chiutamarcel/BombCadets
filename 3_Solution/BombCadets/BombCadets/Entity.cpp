#include "Entity.h"

Entity::Entity(sf::Vector2f position, sf::Vector2f size)
{
	shape.setPosition(position);
	shape.setSize(size);
	shape.setScale(sf::Vector2f(1.0f, 1.0f));
}

Entity::Entity(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture):
	Entity(position, size)
{
	shape.setTexture(texture);
}

Entity::Entity(sf::Vector2f position, float length, sf::Texture* texture):
	Entity(position, sf::Vector2f(length, length), texture)
{
}

Entity::Entity(sf::Vector2f position, sf::Vector2f size, sf::Color color):
	Entity(position, size)
{
	shape.setFillColor(color);
}

Entity::Entity(sf::Vector2f position, float length, sf::Color color):
	Entity(position, sf::Vector2f(length, length), color)
{
}

Entity::~Entity()
{
}

void Entity::update(float deltaTime)
{
}

void Entity::pollEvents()
{
}

const sf::RectangleShape& Entity::getShape()
{
	return shape;
}

void Entity::setPosition(sf::Vector2f _position)
{
	shape.setPosition(_position);
}

const sf::Vector2f& Entity::getPosition() const
{
	return shape.getPosition();
}

void Entity::setTexture(sf::Texture* texture)
{
	shape.setTexture(texture);
}
