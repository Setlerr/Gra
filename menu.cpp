#include "menu.hpp"

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("arcade.ttf"))
	{
		return;
	}
	menu[0].setFont(font);	
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("NEW GAME");
	menu[0].setPosition(sf::Vector2f(width / 4, height / (MAX_MENU_LEVELS + 1) * 1));
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("LAST RECORDS");
	menu[1].setPosition(sf::Vector2f(width / 4, height / (MAX_MENU_LEVELS + 1) * 2));
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("HELP");
	menu[2].setPosition(sf::Vector2f(width / 4, height / (MAX_MENU_LEVELS + 1) * 3));
	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("EXIT");
	menu[3].setPosition(sf::Vector2f(width / 4, height / (MAX_MENU_LEVELS + 1) * 4));

}
void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_MENU_LEVELS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUpM()
{
	if (selectedItem >= 0 && selectedItem < MAX_MENU_LEVELS)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem--;
		if (selectedItem < 0)
			selectedItem = MAX_MENU_LEVELS - 1;
		menu[selectedItem].setFillColor(sf::Color::Red);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
	
	
}

void Menu::MoveDownM()
{
	if (selectedItem >= 0 && selectedItem < MAX_MENU_LEVELS)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem++;
		if (selectedItem >= MAX_MENU_LEVELS)
			selectedItem = 0;
		menu[selectedItem].setFillColor(sf::Color::Red);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
	
}

