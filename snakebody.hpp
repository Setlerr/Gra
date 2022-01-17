
#ifndef _SNAKEBODY_HPP
#define _SNAKEBODY_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

class SnakeBody 
{
private:
    Vector2f position;
    RectangleShape body;
public:
    explicit SnakeBody(Vector2f startPosition);

    Vector2f getPosition();
    void setPosition(Vector2f newPosition);

    RectangleShape getShape();

    void update();
};


#endif 
