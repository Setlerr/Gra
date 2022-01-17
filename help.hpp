#ifndef _HELP_HPP
#define _HELP_HPP

#include <SFML/Graphics.hpp>

using namespace sf;
class Help
{

private:
	Font font;
	Text help;
	Vector2f resolution;
	RenderWindow window;

public:
	Help();
	void drawH();
	void runH();
};


#endif
