#include "snakebody.hpp"

SnakeBody::SnakeBody(Vector2f startPosition) 
{
	body.setSize(Vector2f(20, 20));
	body.setFillColor(Color::Green);
	body.setPosition(startPosition);
	position = startPosition;
}

Vector2f SnakeBody::getPosition() 
{
	return position;
}

void SnakeBody::setPosition(Vector2f newPosition) 
{
	position = newPosition;
}

RectangleShape SnakeBody::getShape() 
{
	return body;
}

void SnakeBody::update() 
{
	body.setPosition(position);
}
