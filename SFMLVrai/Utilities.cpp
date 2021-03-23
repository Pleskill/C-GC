#include "Utilities.h"

void Utilities::setShapeOrigine(sf::Shape* forme, float x, float y)
{
	forme->setOrigin(forme->getLocalBounds().width * x, forme->getLocalBounds().height * y);
}

void Utilities::setObjectPosition(sf::Shape* forme, int x, int y)
{
	if (x > WIDTH)
	{
		x = WIDTH;
	}
	if (y = HEIGHT)
	{
		y = HEIGHT;
	}

	forme->setPosition(x, y);
}

//bool Utilities::isColliding(sf::Shape* forme, sf::Vector2f* vitesse)
//{
//	sf::FloatRect shapeCollider = forme->getGlobalBounds();
//
//	if(shapeCollider.intersects())
//
//	return false;
//}