#include "NPC.h" 
#include "src/AStar.h"
#include "mapOfNodes.h"
#include "Entities.h"

void NPC::printNodes()
{
	for (int i = 0; i < 21; i++)
		std::cout << i %10;
	std::cout << std::endl;
	for (int i = 0; i < 11; std::cout<<i, i++, std::cout << std::endl)
		for (int j = 0; j < 21; j++)
		{
			switch (mapOfNodes::getInstance().getEntityNodes()[i][j].getType())
			{
			case EntityType::CHARACTER:
				std::cout << "C";
				break;
			case EntityType::BREAKABLE_WALL:
				std::cout << "B";
				break;
			case EntityType::UNBREAKABLE_WALL:
				std::cout << "U";
				break;
			case EntityType::PATH:
				std::cout << "P";
				break;
			default:
				break;
			}
		}
		std::cout << "start: " << this->shape.getPosition().y / 64 - 2<< " " << this->shape.getPosition().x / 64 << std::endl;
		std::cout << "goal: " << mapOfNodes::getInstance().getGoal()->getY() << " " << mapOfNodes::getInstance().getGoal()->getX() << std::endl;
		for (auto it : mapOfNodes::getInstance().getPath())
		{
			std::cout << it->getY()/64 << " " << it->getX()/64 << std::endl;
		}
}

void NPC::movement(float deltaTime)
{
	float directX = mapOfNodes::getInstance().getPath().back()->getX() - this->shape.getPosition().x;
	float directY = mapOfNodes::getInstance().getPath().back()->getY() - this->shape.getPosition().y;
	sf::Vector2f direction = sf::Vector2f(directX, directY);
	velocity = direction * speed * deltaTime;
}

void NPC::whereToGo()
{
	mapOfNodes::getInstance().updateMapOfNodes();
	mapOfNodes::getInstance().setStart(this->shape.getPosition().y / 64 - 2, this->shape.getPosition().x /64);
	mapOfNodes::getInstance().setGoal();
	if (mapOfNodes::getInstance().findPath() == 0)
	{
		mapOfNodes::getInstance().setSecondaryGoal();
		mapOfNodes::getInstance().findPath();
	}
	printNodes();

	if (mapOfNodes::getInstance().distanceToGoal() < 64 && (mapOfNodes::getInstance().getGoal()->getType() == EntityType::CHARACTER || mapOfNodes::getInstance().getGoal()->getType() == EntityType::BREAKABLE_WALL))
	{
		Entities::getInstance().getBombs().push_back(new Bomb(this->getShape().getPosition() + sf::Vector2f(16.f, 16.f), 32.f, sf::Color::Magenta));
		if (this->planted.getElapsedTime().asSeconds() >= 3)
			this->planted.restart();
	}

	for (auto it : Entities::getInstance().getBombs())
	{
		float distX = it->getShape().getPosition().x - this->shape.getPosition().x;
		float distY = it->getShape().getPosition().y - this->shape.getPosition().y;
		if (sqrt(distX * distX + distY * distY) < 128)
		{
			mapOfNodes::getInstance().setPathToRunFromBomb();
		}
	}
}

NPC::NPC(sf::Vector2f position, sf::Vector2f size, float speed) :
	Character(position, size, speed)
{
}

NPC::NPC(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, float speed) :
	Character(position, size, texture, speed)
{
}

NPC::NPC(sf::Vector2f position, float length, sf::Texture* texture, float speed) :
	Character(position, length, texture, speed)
{
}

NPC::NPC(sf::Vector2f position, sf::Vector2f size, sf::Color color, float speed) :
	Character(position, size, color, speed)
{
}

NPC::NPC(sf::Vector2f position, float length, sf::Color color, float speed) :
	Character(position, length, color, speed)
{
}

NPC::~NPC()
{
}

void NPC::update(float deltaTime)
{
	Character::update(deltaTime);
	this->whereToGo();
	this->movement(deltaTime);
}

