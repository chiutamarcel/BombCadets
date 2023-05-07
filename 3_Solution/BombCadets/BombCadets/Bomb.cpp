#include "Bomb.h"
#include "Entities.h"

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
	
	Entities::getInstance().getExplosions().push_back(new Explosion(this->getShape().getPosition(), sf::Vector2f(64.f, 64.f), sf::Color::Yellow));
	Entities::getInstance().getExplosions().push_back(new Explosion(this->getShape().getPosition() + sf::Vector2f(0.f, 64.f), sf::Vector2f(64.f, 64.f), sf::Color::Yellow));
	Entities::getInstance().getExplosions().push_back(new Explosion(this->getShape().getPosition() + sf::Vector2f(0.f, -64.f), sf::Vector2f(64.f, 64.f), sf::Color::Yellow));
	Entities::getInstance().getExplosions().push_back(new Explosion(this->getShape().getPosition() + sf::Vector2f(64.f, 0.f), sf::Vector2f(64.f, 64.f), sf::Color::Yellow));
	Entities::getInstance().getExplosions().push_back(new Explosion(this->getShape().getPosition() + sf::Vector2f(-64.f, 0.f), sf::Vector2f(64.f, 64.f), sf::Color::Yellow));
	
	delete this;
}

Bomb::~Bomb() {}