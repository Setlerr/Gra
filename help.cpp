#include "help.hpp"


Help::Help()
{
	resolution = Vector2f(800, 600);
	window.create(VideoMode(resolution.x, resolution.y), "MENU HELP", Style::Default);
	window.setFramerateLimit(60);
	if (!font.loadFromFile("arcade.ttf"))
	{
		return;
	}
	help.setFont(font);
	help.setFillColor(sf::Color::Red);
	help.setString("USE W,A,S,D TO CHANGE DIRECTION MOVEMENT\n\n\nUSE SPACE TO PAUSE");
	help.setPosition(sf::Vector2f(800 / 6, 600 / 6));
}
void Help::drawH()
{

	window.clear();
	window.draw(help);
	window.display();

}
void Help::runH()
{
    while (window.isOpen())
    {
        drawH();
    }
}