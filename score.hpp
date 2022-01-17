#ifndef _SCORE_HPP
#define _SCORE_HPP

#include <SFML/Graphics.hpp>


using namespace sf;
class Score
{

private:
	Font font;
	Text score;
	Vector2f resolution;
	RenderWindow window;

public:
	Score();
	void drawS();
	void runS();
};


#endif
