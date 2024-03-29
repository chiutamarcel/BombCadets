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
	shape.setScale(0.0f, 0.0f);
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
		shape.setScale(shape.getScale().x + 0.005f, shape.getScale().y + 0.005f);
		shape.setPosition(shape.getPosition().x - 0.15f, shape.getPosition().y - 0.15f);
		checkCollision();
		if (shape.getScale().x > 1.0f) {
			growing = false;
		}
	}
	else {
		shape.setScale(shape.getScale().x - 0.0005f, shape.getScale().y - 0.0005f);
		shape.setPosition(shape.getPosition().x + 0.015f, shape.getPosition().y + 0.015f);
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
	//for (auto fire : Entities::getInstance().getExplosions())
	//{
	//	for (auto breakableBlock : Entities::getInstance().getBreakableBlocks())
	//		if (fire->getShape().getGlobalBounds().intersects(breakableBlock->getShape().getGlobalBounds()))
	//		{
	//			Entities::getInstance().removeBreakableBlock(breakableBlock);
	//			delete breakableBlock;
	//		}
	//	for (auto character : Entities::getInstance().getCharacters())
	//		if (fire->getShape().getGlobalBounds().intersects(character->getShape().getGlobalBounds()))
	//		{
	//			Entities::getInstance().removeCharacter(character);
	//			delete character;
	//		}
	//	for (auto walls : Entities::getInstance().getWalls())
	//		if (fire->getShape().getGlobalBounds().intersects(walls->getShape().getGlobalBounds()))
	//		{
	//			Entities::getInstance().removeExplosion(fire);
	//			delete fire;
	//		}
	//}
	
	for (auto breakableBlock : Entities::getInstance().getBreakableBlocks())
		if (this->getShape().getGlobalBounds().intersects(breakableBlock->getShape().getGlobalBounds()))
		{
			Entities::getInstance().removeBreakableBlock(breakableBlock);
			delete breakableBlock;
		}
	for (auto character : Entities::getInstance().getCharacters())
		if (this->getShape().getGlobalBounds().intersects(character->getShape().getGlobalBounds()))
		{
			Entities::getInstance().removeCharacter(character);
			delete character;
		}
	for (auto walls : Entities::getInstance().getWalls())
		if (this->getShape().getGlobalBounds().intersects(walls->getShape().getGlobalBounds()))
		{
			Entities::getInstance().removeExplosion(this);
			//delete this;
		}
	
}

Explosion::~Explosion()
{
}
