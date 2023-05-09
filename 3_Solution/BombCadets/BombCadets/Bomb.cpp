#include "Bomb.h"
#include "Entities.h"
#include <cmath>
#include <cassert>

Bomb::Bomb(sf::Vector2f position, sf::Vector2f size) :
	WorldObject(position, size) {
	planted.restart();
}

Bomb::Bomb(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture) :
	WorldObject(position, size, texture) {
	planted.restart();
}

Bomb::Bomb(sf::Vector2f position, float length, sf::Texture* texture) :
	WorldObject(position, length, texture) {
	planted.restart();
}

Bomb::Bomb(sf::Vector2f position, sf::Vector2f size, sf::Color color) :
	WorldObject(position, size, color) {
	planted.restart();
}

Bomb::Bomb(sf::Vector2f position, float length, sf::Color color) :
	WorldObject(position, length, color) {
	planted.restart();
}

void Bomb::update(float deltaTime)
{
	if (planted.getElapsedTime().asSeconds() > 3.f)
	{
		explode();
	}
	
}

void Bomb::explode()
{
	Entities::getInstance().removeBomb(this);
	
	Entities::getInstance().getExplosions().push_back(new Explosion(getPositionExplosion(), sf::Vector2f(58.f, 56.f), sf::Color::Yellow));
	Entities::getInstance().getExplosions().push_back(new Explosion(getPositionExplosion() + sf::Vector2f(0.f, 64.f), sf::Vector2f(56.f, 56.f), sf::Color::Yellow));
	Entities::getInstance().getExplosions().push_back(new Explosion(getPositionExplosion() + sf::Vector2f(0.f, -64.f), sf::Vector2f(56.f, 56.f), sf::Color::Yellow));
	Entities::getInstance().getExplosions().push_back(new Explosion(getPositionExplosion() + sf::Vector2f(64.f, 0.f), sf::Vector2f(56.f, 56.f), sf::Color::Yellow));
	Entities::getInstance().getExplosions().push_back(new Explosion(getPositionExplosion() + sf::Vector2f(-64.f, 0.f), sf::Vector2f(56.f, 56.f), sf::Color::Yellow));
	
	//Entities::getInstance().getExplosions().push_back(new Explosion());
	
	delete this;
}

Bomb::~Bomb() {}

// this is to spawn the explosion correctly
sf::Vector2f Bomb::getPositionExplosion()
{
	sf::Vector2f position = this->shape.getPosition();
	position.x = std::round(position.x / 64.f) * 64.f + 32.f;
	position.y = std::round(position.y / 64.f) * 64.f + 32.f;
	return position;
}