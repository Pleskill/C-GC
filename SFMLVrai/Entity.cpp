#include "Entity.h"
#include "Utilities.h"

Utilities Util;

void Brick::create()
{
	brick = new sf::RectangleShape(sf::Vector2f(width, height));
	brick->setPosition(0, 0);
}

sf::Vector2f Brick::getPos()
{
	return brick->getPosition();
}

void Brick::setPos(sf::Shape* prop, sf::Vector2f pos)
{
    if (pos.x > Util.WIDTH_W)
    {
        pos.x = Util.WIDTH_W;
    }
    if (pos.y > Util.HEIGHT_W)
    {
        pos.y = Util.HEIGHT_W;
    }

    prop->setPosition(pos);
}


void Ball::create()
{
	ball = new sf::CircleShape(20.f);
	ball->setPosition(0, 0);
}

sf::Vector2f Ball::getPos()
{
	return ball->getPosition();
}

void Ball::setPos(sf::Shape* prop, sf::Vector2f pos)
{
    if (pos.x > Util.WIDTH_W)
    {
        pos.x = Util.WIDTH_W;
    }
    if (pos.y > Util.HEIGHT_W)
    {
        pos.y = Util.HEIGHT_W;
    }

    prop->setPosition(pos);
}