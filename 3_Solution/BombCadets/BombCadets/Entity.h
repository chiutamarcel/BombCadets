#pragma once

#include "SFML/Graphics.hpp"

class Entity
{
protected:
	sf::RectangleShape shape;
	Entity(sf::Vector2f position, sf::Vector2f size);

public:
	
	// Constructors / Destructors
	Entity(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture);
	Entity(sf::Vector2f position, float length, sf::Texture* texture);
	Entity(sf::Vector2f position, sf::Vector2f size, sf::Color color);
	Entity(sf::Vector2f position, float length, sf::Color color);
	~Entity();

	// Functions
	virtual void update(float deltaTime);

	// Getters / Setters
	const sf::RectangleShape& getShape();
};

