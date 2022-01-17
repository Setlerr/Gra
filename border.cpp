#include "border.hpp"

Border::Border(Vector2f position, Vector2f size) 
{
	borderShape.setSize(size);
	borderShape.setFillColor(Color::Magenta);
	borderShape.setPosition(position);
}

RectangleShape Border::getShape() 
{
	return borderShape;
}