#include "WorldObject.h"

WorldObject::WorldObject(sf::Vector2f position,sf::Vector2f size) :
	Entity(position, size){}

WorldObject::WorldObject(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture) :
	Entity(position, size, texture) {}

WorldObject::WorldObject(sf::Vector2f position, float length, sf::Texture* texture) :
	Entity(position, length, texture) {}

WorldObject::WorldObject(sf::Vector2f position, sf::Vector2f size, sf::Color color) :
	Entity(position, size, color) {}

WorldObject::WorldObject(sf::Vector2f position, float length, sf::Color color) :
	Entity(position, length, color) {}
