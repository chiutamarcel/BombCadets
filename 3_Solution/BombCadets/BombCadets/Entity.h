#pragma once

#include <fstream>
#include <iostream>
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
	virtual ~Entity();

	// Functions
	virtual void update(float deltaTime);
	virtual void pollEvents();

	// Getters / Setters
	const sf::RectangleShape& getShape();

	void setPosition(sf::Vector2f _position);
	const sf::Vector2f& getPosition() const;

	void setTexture(sf::Texture* texture);
};

//static std::vector<Entity*> entities;
