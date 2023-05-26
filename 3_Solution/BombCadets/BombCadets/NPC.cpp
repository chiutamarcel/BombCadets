#include "NPC.h"
#include "MapOfNodes.h"
#include "Entities.h"

NPC::NPC(sf::Vector2f position, sf::Vector2f size, float speed):
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
	whereToGo();
	movement(deltaTime);
}

void NPC::movement(float deltaTime)
{
	sf::Vector2f direction = sf::Vector2f(0, 0);

	if (MapOfNodes::getInstance()->getPath().size() > 0)
	{
		MapOfNodes::getInstance()->getPath().pop_back();

		MapOfNodes::getInstance()->setOption(0);
		if (MapOfNodes::getInstance()->getPath().back()->getType() == EntityType::PATH) {
			if (MapOfNodes::getInstance()->getPath().back()->getY() < this->getShape().getPosition().y - 2)
				direction = sf::Vector2f(0.0f, -1.0f);
			else if (MapOfNodes::getInstance()->getPath().back()->getY() > this->getShape().getPosition().y + 2)
				direction = sf::Vector2f(0.0f, 1.0f);
			else if (MapOfNodes::getInstance()->getPath().back()->getX() < this->getShape().getPosition().x - 2)
				direction = sf::Vector2f(-1.0f, 0.0f);
			else if (MapOfNodes::getInstance()->getPath().back()->getX() > this->getShape().getPosition().x + 2)
				direction = sf::Vector2f(1.0f, 0.0f);
		}
		else if (MapOfNodes::getInstance()->getPath().back()->getType() == EntityType::BREAKABLE_WALL && this->planted.getElapsedTime().asSeconds() > 3.f)
		{
			Entities::getInstance().getBombs().push_back(new Bomb(this->getShape().getPosition() + sf::Vector2f(16.f, 16.f), 32.f, sf::Color::Magenta));
			if (this->planted.getElapsedTime().asSeconds() >= 3)
				this->planted.restart();
		}
	}

	this->velocity = direction * speed * deltaTime;
}

void NPC::whereToGo()
{
	for (auto it : Entities::getInstance().getBombs())
	{
		if (distanceTo(it->getShape().getPosition()) < 192)
		{
			MapOfNodes::getInstance()->setOption(1);
			break;
		}
	}
	MapOfNodes::getInstance()->updateMapOfNodes();
	if (MapOfNodes::getInstance()->getOption() == 0)
	{
		MapOfNodes::getInstance()->setStart(this->getShape().getPosition().y / 64 - 2, this->getShape().getPosition().x / 64);
		MapOfNodes::getInstance()->setGoal();
		if (!MapOfNodes::getInstance()->findPath())
		{
			std::cout << "Path not found" << std::endl;
			return;
		}
	}
	else
	{
		MapOfNodes::getInstance()->runFromBomb();
	}
}

void NPC::printNodes()
{
	for (int i = 0; i < 21; i++)
		std::cout << i % 10;
	std::cout << std::endl;
	for (int i = 0; i < 11; std::cout << i, i++, std::cout << std::endl)
		for (int j = 0; j < 21; j++)
		{
			switch (MapOfNodes::getInstance()->getEntityNodes()[i][j].getType())
			{
			case EntityType::CHARACTER:
				std::cout << "C";
				break;
			case EntityType::PATH:
				std::cout << "_";
				break;
			case EntityType::BREAKABLE_WALL:
				std::cout << "#";
				break;
			case EntityType::UNBREAKABLE_WALL:
				std::cout << "@";
			default:
				break;
			}
		}
	std::cout << "start: " << MapOfNodes::getInstance()->getStart()->getY()/64 - 2 << " " << MapOfNodes::getInstance()->getStart()->getX() / 64 << std::endl;
	std::cout << "goal: " << MapOfNodes::getInstance()->getGoal()->getY() / 64 - 2 << " " << MapOfNodes::getInstance()->getGoal()->getX() / 64 << std::endl;
	for (auto it : MapOfNodes::getInstance()->getPath())
	{
		std::cout << it->getY() / 64 - 2 << " " << it->getX() / 64 << std::endl;
	}
}

float NPC::distanceTo(sf::Vector2f position)
{
	int y = position.y - this->getShape().getPosition().y;
	int x = position.x - this->getShape().getPosition().x;

	return sqrt(x * x + y * y);
}