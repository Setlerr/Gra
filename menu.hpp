#ifndef _MENU_HPP
#define _MENU_HPP

#include <SFML/Graphics.hpp>

#define MAX_MENU_LEVELS 4
using namespace sf;
class Menu
{

private:
	Font font;
	Text menu[MAX_MENU_LEVELS]; 
	int selectedItem = 0;


public:
	Menu(float width, float height);
	~Menu() {};
	void MoveUpM();
	void MoveDownM();
	int getSelectedItem() 
	{ 
		return selectedItem; 
	}
	void draw(RenderWindow &window);
};


#endif
