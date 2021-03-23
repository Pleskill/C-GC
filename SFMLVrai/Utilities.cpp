#include "Utilities.h"

sf::Vector2f startPos(0,0);

void Utilities::setShapeOrigine(sf::Shape* shape, float x, float y)
{
    shape->setOrigin(shape->getLocalBounds().width * x, shape->getLocalBounds().height * y);
}

void Utilities::setObjectPosition(sf::Shape* shape, sf::Vector2f pos)
{
    if (pos.x > WIDTH_W)
    {
        pos.x = WIDTH_W;
    }
    if (pos.y > HEIGHT_W)
    {
        pos.y = HEIGHT_W;
    }

    shape->setPosition(pos);
    startPos = pos;
}

bool Utilities::isColliding(sf::Shape* shape)
{
    //On check si la hauteur de la balle dépasse un des bords de la fenêtre
    if (shape->getPosition().y + shape->getLocalBounds().height / 2 > HEIGHT_W)
    {
        shape->setPosition(shape->getPosition().x, shape->getPosition().y - 5);
        return true;

        shape->setPosition(startPos); //TODO si la balle sors par en dessous de l'écran'
        blocked = false;
    }
    else if (shape->getPosition().y - shape->getLocalBounds().height / 2 < 0)
    {
        shape->setPosition(shape->getPosition().x, shape->getPosition().y + 5);
        return true;
    }
    else
        return false;

    //On check si la largeur de la balle dépasse la fenêtre
    if (shape->getPosition().x + shape->getLocalBounds().width / 2 > WIDTH_W)
    {
        shape->setPosition(shape->getPosition().x - 5, shape->getPosition().y);
        return true;
    }
    else if(shape->getPosition().x - shape->getLocalBounds().width / 2 < 0)
    {
        shape->setPosition(shape->getPosition().x + 5, shape->getPosition().y);
        return true;
    }
    else
        return false;

    return false;
    //C'est plus KC'
}