#include "Utilities.h"

void Utilities::setShapeOrigine(sf::Shape* shape, float x, float y)
{
	shape->setOrigin(shape->getLocalBounds().width * x, shape->getLocalBounds().height * y);
}

void Utilities::setObjectPosition(sf::Shape* shape, int x, int y)
{
	if (x > WIDTH_W)
	{
		x = WIDTH_W;
	}
	if (y = HEIGHT_W)
	{
		y = HEIGHT_W;
	}

	shape->setPosition(x, y);
}

bool Utilities::isColliding(sf::Shape* shape)
{
	//On check si la hauteur de la balle dépasse un des bords de la fenêtre
	if (shape->getOrigin().y + shape->getLocalBounds().height/2 > HEIGHT_W || shape->getOrigin().y - shape->getLocalBounds().height/2 < 0)
	{
		return true;
	}
	else
		return false;

	//On check si la largeur de la balle dépasse la fenêtre
	if (shape->getOrigin().x + shape->getLocalBounds().width/2 > WIDTH_W || shape->getOrigin().x - shape->getLocalBounds().width/2 < 0)
	{
		return true;
	}
	else
		return false;

	return false;
}