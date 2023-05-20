#include "NPC.h" 
#include "src/AStar.h"

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
	
}



