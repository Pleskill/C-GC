#include "Utilities.h"

void Utilities::setShapeOrigine(sf::Shape* forme, float x, float y)
{
	forme->setOrigin(forme->getLocalBounds().width * x, forme->getLocalBounds().height * y);
}