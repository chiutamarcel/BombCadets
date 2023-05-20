#pragma once
#include "Character.h"
class NPC :
    public Character
{
public:
    NPC(sf::Vector2f position, sf::Vector2f size, float speed = 0);
	NPC(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, float speed = 0);
	NPC(sf::Vector2f position, float length, sf::Texture* texture, float speed = 0);
	NPC(sf::Vector2f position, sf::Vector2f size, sf::Color color, float speed = 0);
	NPC(sf::Vector2f position, float length, sf::Color color, float speed = 0);
	~NPC();

	virtual void update(float deltaTime) override;
};

