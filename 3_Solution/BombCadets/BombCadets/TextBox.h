#pragma once
#include "UIElement.h"
#include <sstream>
#include <iostream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class TextBox : public UIElement
{
public:
	TextBox() : UIElement() {}

	TextBox(int size, sf::Color color, bool sel);

	void setFont();

	void setPosition(sf::Vector2f pos)
	{
		textbox.setPosition(pos);
	}

	void setLimit(bool ToF)
	{
		hasLimit = ToF;
	}

	void setLimit(bool ToF, int lim)
	{
		hasLimit = ToF;
		limit = lim;
	}

	void setSelected(bool sel);

	std::string getText()
	{
		return text.str();
	}

	void draw(sf::RenderWindow* window);

	void char_entered(sf::Event input);

	void setAsPass();

	bool getSelection()
	{
		return isSelected;
	}

	void setSelect(bool selection)
	{
		isSelected = selection;
	}

private:

	sf::Text textbox;
	std::ostringstream text;
	bool isSelected = true;
	bool hasLimit = true;
	int limit = 32;
	sf::Font font;

	void actual_char(int charTyped)
	{
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
		{
			text << static_cast<char>(charTyped);
		}
		else if (charTyped == DELETE_KEY)
		{
			if (text.str().length() > 0)
			{
				deleteLastChar();
			}
		}

		textbox.setString(text.str() + "_");
	}
	
	void deleteLastChar()
	{
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length() - 1; ++i)
		{
			newT += t[i];
		}
		text.str("");
		text << newT;
		textbox.setString(text.str());
	}

};

