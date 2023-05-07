#include "Explosion.h"
#include "Entities.h"

Explosion::Explosion(sf::Vector2f position, sf::Vector2f size) :
	WorldObject(position, size) {
	alive = true;
	growing = true;
	shape.setScale(0.5f, 0.5f);
}

Explosion::Explosion(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture) :
	WorldObject(position, size, texture) {
	alive = true;
	growing = true;
	shape.setScale(0.5f, 0.5f);
}

Explosion::Explosion(sf::Vector2f position, float length, sf::Texture* texture) :
	WorldObject(position, length, texture) {
	alive = true;
	growing = true;
	shape.setScale(05.f, 0.5f);
}

Explosion::Explosion(sf::Vector2f position, sf::Vector2f size, sf::Color color) :
	WorldObject(position, size, color) {
	alive = true;
	growing = true;
	shape.setScale(0.5f, 0.5f);
}

Explosion::Explosion(sf::Vector2f position, float length, sf::Color color) :
	WorldObject(position, length, color) {
	alive = true;
	growing = true;
	shape.setScale(0.5f, 0.5f);
}

void Explosion::update(float deltaTime)
{
	//make it with time
	if (growing) {
		shape.setScale(shape.getScale().x + 0.01f, shape.getScale().y + 0.01f);
		checkCollision();
		if (shape.getScale().x > 1.0f) {
			growing = false;
		}
	}
	else {
		shape.setScale(shape.getScale().x - 0.0003f, shape.getScale().y - 0.0003f);
		if (shape.getScale().x < 0.65f) {
			removeExplosion();
		}
	}
}

sf::Vector2f Explosion::getScale()
{
	return shape.getScale();
}

void Explosion::setScale(float x, float y)
{
	shape.setScale(x, y);
}

void Explosion::removeExplosion()
{
	Entities::getInstance().removeExplosion(this);
	
	delete this;
}

void Explosion::checkCollision()
{
	for (auto fire : Entities::getInstance().getExplosions())
	{
		for (auto breakableBlock : Entities::getInstance().getBreakableBlocks())
			if (fire->getShape().getGlobalBounds().intersects(breakableBlock->getShape().getGlobalBounds()))
			{
				Entities::getInstance().removeBreakableBlock(breakableBlock);
				delete breakableBlock;
			}
		for (auto character : Entities::getInstance().getCharacters())
			if (fire->getShape().getGlobalBounds().intersects(character->getShape().getGlobalBounds()))
			{
				Entities::getInstance().removeCharacter(character);
				delete character;
			}
	}
}

Explosion::~Explosion()
{
}
