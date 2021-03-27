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
int Ball::isColliding(sf::Shape* shape, sf::Shape* other)
{
    int side = 0; //On définit un int qui nous dit ou la collision avec la balle à lieu

#pragma region Collisions écran
    //On check si la hauteur de la balle dépasse un des bords de la fenêtre
    if (shape->getPosition().y + shape->getLocalBounds().height / 2 > Util.HEIGHT_W)
    {
        side = 2;
    }
    else if (shape->getPosition().y - shape->getLocalBounds().height / 2 < 0)
    {
        side = 1;
        shape->setPosition(shape->getPosition().x, shape->getPosition().y + 5);
    }

    //On check si la largeur de la balle dépasse la fenêtre
    if (shape->getPosition().x + shape->getLocalBounds().width / 2 > Util.WIDTH_W)
    {
        side = 3;
        shape->setPosition(shape->getPosition().x - 5, shape->getPosition().y);
    }
    else if (shape->getPosition().x - shape->getLocalBounds().width / 2 < 0)
    {
        side = 4;
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
            side = 3;
        }
        //Si elle tape sur la droite
        else if (distDroite < distGauche && distDroite < distHaut && distDroite < distBas)
        {
            side = 4;
        }
        //Si elle tape en haut
        else if (distHaut < distGauche && distHaut < distDroite && distHaut < distBas)
        {
            side = 2;
        }
        //Et dans le dernier cas, collision en bas
        else
            side = 1;
    }
#pragma endregion

    return side;
}