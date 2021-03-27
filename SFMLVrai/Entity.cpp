#include "Entity.h"
#include "Utilities.h"
#include <math.h>

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

    //On set la direction de la balle en prévision
    dir.x = 0;
    dir.y = 0;
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

//Retourne le côté de la collision, pour une meilleure gestion des rebonds
sf::Vector2f Ball::isColliding(sf::Shape* shape, sf::Shape* other)
{
    sf::Vector2f startPosition(Util.WIDTH_W / 2, Util.HEIGHT_W - shape->getLocalBounds().height / 2);

#pragma region Collisions écran
    //On check si la hauteur de la balle dépasse un des bords de la fenêtre
    if (shape->getPosition().y + shape->getLocalBounds().height / 2 > Util.HEIGHT_W)
    {
        dir.x = 0;
        dir.y = 0;
        speed = 0;
        shape->setPosition(startPosition);
        Util.blocked = false;
    }
    else if (shape->getPosition().y - shape->getLocalBounds().height / 2 < 0)
    {
        dir.y = -dir.y;
        shape->setPosition(shape->getPosition().x, shape->getPosition().y + 5);
    }

    //On check si la largeur de la balle dépasse la fenêtre
    if (shape->getPosition().x + shape->getLocalBounds().width / 2 > Util.WIDTH_W)
    {
        dir.x = -dir.x;
        shape->setPosition(shape->getPosition().x - 5, shape->getPosition().y);
    }
    else if (shape->getPosition().x - shape->getLocalBounds().width / 2 < 0)
    {
        dir.x = -dir.x;
        shape->setPosition(shape->getPosition().x + 5, shape->getPosition().y);
    }
#pragma endregion

#pragma region Collision Autre
    if (shape->getGlobalBounds().intersects(other->getGlobalBounds()))
    {
        float distGauche = abs(shape->getGlobalBounds().width - other->getGlobalBounds().left);
        float distDroite = abs(shape->getGlobalBounds().left - other->getGlobalBounds().width);
        float distHaut = abs(shape->getGlobalBounds().height - other->getGlobalBounds().top);
        float distBas = abs(shape->getGlobalBounds().top - other->getGlobalBounds().height);

        //Si la balle tape sur la gauche de l'objet
        if (distGauche < distDroite && distGauche < distHaut && distGauche < distBas)
        {
            dir.x = -dir.x;
        }
        //Si elle tape sur la droite
        else if (distDroite < distGauche && distDroite < distHaut && distDroite < distBas)
        {
            dir.x = -dir.x;
        }
        //Si elle tape en haut
        else if (distHaut < distGauche && distHaut < distDroite && distHaut < distBas)
        {
            dir.y = -dir.y;
        }
        //Et dans le dernier cas, collision en bas
        else
            dir.y = -dir.y;
    }
#pragma endregion

    return dir;
}

sf::Vector2f Ball::getDir()
{
    return dir;
}

void Ball::setDir(sf::Vector2f direction)
{
    dir = direction;
}

float Ball::getSpeed()
{
    return speed;
}

void Ball::setSpeed(float s)
{
    speed = s;
}
