#include "game.hpp"
#include "menu.hpp"
#include "help.hpp"
#include "score.hpp"
#include <iostream>
#include <fstream>

void myDelay(int opoznienie)
{
	sf::Clock zegar;
	sf::Time czas;
	while (1)
	{
		czas = zegar.getElapsedTime();
		if (czas.asMilliseconds() > opoznienie)
		{
			zegar.restart();
			break;
		}

	}
}
int main()
{
	int menu_selected_flag = 0;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Snake Menu");
	Menu menu(window.getSize().x, window.getSize().y);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}


			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up)
				{
					myDelay(250);
					menu.MoveUpM();
				}

				if (event.key.code == sf::Keyboard::Down)
				{
					myDelay(250);
					menu.MoveDownM();
				}
				if (menu_selected_flag == 0)
				{
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 0)
					{
						window.close();
						Game game;
						game.run();
					}
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1)
					{
						menu_selected_flag = 1;
						Score score;
						score.runS();
					}

					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2)
					{
						menu_selected_flag = 1;
						window.close();
						Help help;
						help.runH();
					}
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 3)
					{
						menu_selected_flag = 1;
						window.close();

					}

				}


			}
			window.clear();

			if (menu_selected_flag == 0)
				menu.draw(window);
			window.display();
		}

	}
	return 0;
}

  

