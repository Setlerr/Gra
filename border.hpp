#ifndef _BORDER_HPP
#define _BORDER_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

class Border 
{
private:
    RectangleShape borderShape;

public:
    Border(Vector2f position, Vector2f size);

    RectangleShape getShape();
};


#endif 
