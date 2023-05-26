#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#pragma once
class UIElement
{
public:
	virtual void draw(sf::RenderWindow* window) = 0;

	UIElement() {};
	~UIElement() {};
};

