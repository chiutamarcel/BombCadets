#include "TextBox.h"

TextBox::TextBox(int size, sf::Color color, bool sel) : UIElement()
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

void TextBox::setFont()
{
	font.loadFromFile("Fonts/SpaceMission.otf");
	textbox.setFont(font);
}

void TextBox::setSelected(bool sel)
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

void TextBox::draw(sf::RenderWindow* window)
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

void TextBox::char_entered(sf::Event input)
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
					actual_char(charTyped);
				}

			}
			else
			{
				actual_char(charTyped);
			}
		}
	}
}

void TextBox::setAsPass()
{
	std::string buffy = "";
	for (int i = 0; i < text.str().length(); ++i)
	{
		buffy += "*";
	}
	textbox.setString(buffy);
}
