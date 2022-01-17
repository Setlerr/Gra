#ifndef _APPLE_HPP
#define _APPLE_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

class Apple 
{
private:
    RectangleShape sprite;

public:
    Apple();

    void setPosition(Vector2f newPosition);
    RectangleShape getSprite();
};


#endif
