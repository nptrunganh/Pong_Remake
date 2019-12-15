#include "Menu.h"

Menu::Menu(float width, float height)
{
	font.loadFromFile("font140.otf");
	menu[0].setFont(font);
	menu[0].setFillColor(Color::Red);
	menu[0].setString("Single");
	menu[0].setPosition(width / 1.5, height / 2);

	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString("2 Player");
	menu[1].setPosition(width / 2 - 20, height / 1.5);

	menu[2].setFont(font);
	menu[2].setFillColor(Color::White);
	menu[2].setString("Get Score");
	menu[2].setPosition(175, 450);
	selectIndex = 0;
}

Menu::~Menu()
{
}

void Menu::Draw(RenderWindow& window)
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::Del(RenderWindow& window)
{
	window.clear(Color::Black);
}

void Menu::MoveUp()
{
	if (selectIndex - 1 >= 0)
	{
		menu[selectIndex].setFillColor(Color::White);
		selectIndex--;
		menu[selectIndex].setFillColor(Color::Red);
	}
}
void Menu::MoveDown()
{
	if (selectIndex + 1 < 3)
	{
		menu[selectIndex].setFillColor(Color::White);
		selectIndex++;
		menu[selectIndex].setFillColor(Color::Red);
	}
}
