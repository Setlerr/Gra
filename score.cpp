#include "score.hpp"
#include <fstream>
#include <iostream>
using namespace std;
string filetosave()
{
	int scorei;
	fstream file;
	file.open("score.txt", ios::in);
	file >> scorei;
	file.close();
	string tmp_text;
	tmp_text += "LAST SCORE: " + std::to_string(scorei);
	return tmp_text;
}

Score::Score()
{

	resolution = Vector2f(800, 600);
	window.create(VideoMode(resolution.x, resolution.y), "SCORE HELP", Style::Default);
	window.setFramerateLimit(60);
	if (!font.loadFromFile("arcade.ttf"))
	{
		return;
	}
	score.setFont(font);
	score.setFillColor(sf::Color::Red);
	score.setString(filetosave());
	score.setPosition(sf::Vector2f(800 / 6, 600 / 6));
}
void Score::drawS()
{

	window.clear();
	window.draw(score);
	window.display();

}
void Score::runS()
{
    while (window.isOpen())
    {
        drawS();
    }
}