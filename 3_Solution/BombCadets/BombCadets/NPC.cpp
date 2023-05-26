#include "NPC.h"
#include "MapOfNodes.h"
#include "Entities.h"
#include "Logger.h"

NPC::NPC(sf::Vector2f position, sf::Vector2f size, float speed):
	Character(position, size, speed)
{
	timer.restart();
}

NPC::NPC(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, float speed) :
	Character(position, size, texture, speed)
{
	timer.restart();
}

NPC::NPC(sf::Vector2f position, float length, sf::Texture* texture, float speed) :
	Character(position, length, texture, speed)
{
	timer.restart();
}

NPC::NPC(sf::Vector2f position, sf::Vector2f size, sf::Color color, float speed) :
	Character(position, size, color, speed)
{
	timer.restart();
}

NPC::NPC(sf::Vector2f position, float length, sf::Color color, float speed) :
	Character(position, length, color, speed)
{
	timer.restart();
}

NPC::~NPC()
{
	Logger::getInstance()->log(LogLevel::INFO, "The NPC died!");
}

void NPC::update(float deltaTime)
{
	if (this->timer.getElapsedTime().asMilliseconds() > 25.f)
	{
		MapOfNodes::getInstance()->getPath().clear();
		whereToGo();
		this->timer.restart();
		movement(deltaTime);
	}
	Character::update(deltaTime);
}

void NPC::movement(float deltaTime)
{
	sf::Vector2f direction = sf::Vector2f(0, 0);

	if (MapOfNodes::getInstance()->getPath().size() > 0)
	{
		MapOfNodes::getInstance()->getPath().pop_back();
		
		if (MapOfNodes::getInstance()->getPath().back()->getType() == EntityType::PATH) {
			EntityNode *aux = MapOfNodes::getInstance()->getPath().back();
			if (MapOfNodes::getInstance()->getPath().back()->getY() < this->getShape().getPosition().y - 4)
				direction = sf::Vector2f(0.0f, -1.0f);
			else if (MapOfNodes::getInstance()->getPath().back()->getY() > this->getShape().getPosition().y + 4)
				direction = sf::Vector2f(0.0f, 1.0f);
			else if (MapOfNodes::getInstance()->getPath().back()->getX() < this->getShape().getPosition().x - 4)
				direction = sf::Vector2f(-1.0f, 0.0f);
			else if (MapOfNodes::getInstance()->getPath().back()->getX() > this->getShape().getPosition().x + 4)
				direction = sf::Vector2f(1.0f, 0.0f);
		
			//if ((aux->getX() != this->getShape().getPosition().y) && (aux->getY() != this->getShape().getPosition().x))
			//if ((aux->getY() + 32 != this->getShape().getPosition().y + 28) && (aux->getX() + 32 != this->getShape().getPosition().x + 28))
			//{
			//	sf::Vector2f diff = -(this->getShape().getPosition() - sf::Vector2f(aux->getX(), aux->getY()));
			//	//direction = diff / sqrt(diff.x * diff.x + diff.y * diff.y);
			//	//if (abs(direction.x) > abs(direction.y)) direction = sf::Vector2f(, 0.0f);
			//	if (abs(diff.x) > abs(diff.y))
			//		direction = sf::Vector2f(1 * diff.x / (abs(diff.x)), 0);
			//	else
			//		direction = sf::Vector2f(0, 1 * diff.y / (abs(diff.y)));
			//}
		}
		else if (MapOfNodes::getInstance()->getPath().back()->getType() == EntityType::BREAKABLE_WALL && this->planted.getElapsedTime().asSeconds() > 3.f)
		{
			Entities::getInstance().spawnBomb(this->getShape().getPosition() + sf::Vector2f(16.f, 16.f));
			//Entities::getInstance().getBombs().push_back(new Bomb(this->getShape().getPosition() + sf::Vector2f(16.f, 16.f), 32.f, sf::Color::Magenta));
			if (this->planted.getElapsedTime().asSeconds() >= 4.f)
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
			Logger::getInstance()->log(LogLevel::ERROR, "Path not found");
			//std::cout << "Path not found" << std::endl;
			return;
		}
	}
	else
	{
		MapOfNodes::getInstance()->runFromBomb();
	}

	if(this->planted.getElapsedTime().asSeconds() > 3.f)
		MapOfNodes::getInstance()->setOption(0);
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