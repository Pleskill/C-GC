#include "Brick.h"

void Brick::createRectangle()
{
	brick = new sf::RectangleShape(sf::Vector2f(width, height));
	brick->setPosition(0, 0);
}

sf::Vector2f Brick::getBrickpos()
{
	return brick->getPosition();
}

void Brick::setBrickPos(sf::Vector2f pos)
{
	brick->setPosition(pos);
}