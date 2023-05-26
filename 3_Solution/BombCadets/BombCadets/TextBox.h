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

	TextBox(int size, sf::Color color, bool sel) : UIElement()
	{
		textbox.setCharacterSize(size);
		textbox.setFillColor(color);
		isSelected = sel;
		if (sel)
		{
			textbox.setString("_");
		}
		else
		{
			textbox.setString("");
		}
	}

	void setFont()
	{
		font.loadFromFile("Fonts/SpaceMission.otf");
		textbox.setFont(font);
	}

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

	void setSelected(bool sel)
	{
		isSelected = sel;
		if (!sel)
		{
			std::string t = text.str();
			std::string newT = "";
			for (int i = 0; i < t.length(); ++i)
			{
				newT += t[i];
			}
			textbox.setString(newT);
		}
	}

	std::string getText()
	{
		return text.str();
	}

	void draw(sf::RenderWindow* window)
	{
		try {
			if (window == nullptr)
				throw std::string("Window is null");

			window->draw(textbox);
		}
		catch (std::string e) {
			std::cout << e << std::endl;
		}
	}

	void typedOn(sf::Event input)
	{
		if (isSelected)
		{
			int charTyped = input.text.unicode;
			if (charTyped < 128)
			{
				if (hasLimit)
				{
					if (text.str().length() <= limit && charTyped == ENTER_KEY)
					{
						if (text.str().length() > 0)
						{
							text.str().pop_back();
						}
						textbox.setString(text.str());
						//setSelect(false);
					}
					else if (text.str().length() > limit && charTyped == DELETE_KEY)
					{
						deleteLastChar();
					}
					else if (text.str().length() <= limit)
					{
						inputLogic(charTyped);
					}
						
				}
				else
				{
					inputLogic(charTyped);
				}
			}
		}
	}

	void setAsPass()
	{
		std::string buffy = "";
		for (int i = 0; i < text.str().length(); ++i)
		{
			buffy += "*";
		}
		textbox.setString(buffy);
	}

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

	void inputLogic(int charTyped)
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

