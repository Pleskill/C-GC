#include <iostream>
#include "Entity.h"
#include "Utilities.h"
#include <math.h>

Utilities Util;

Brick::Brick(float h, float w)
{
    height = h;
    width = w;
}

sf::Vector2f Brick::getPos()
{
	return brickPos;
}

void Brick::setPos(sf::Vector2f pos)
{
    if (pos.x > Util.getWidth())
    {
        pos.x = Util.getWidth();
    }
    if (pos.y > Util.getHeight())
    {
        pos.y = Util.getHeight();
    }

    brickPos = pos;
}

float Brick::getHeight()
{
    return height;
}

float Brick::getWidth()
{
    return width;
}


Ball::Ball(sf::Vector2f d, float s)
{
    dir = d;
    speed = s;
}

sf::Vector2f Ball::getPos()
{
	return ballPos;
}

void Ball::setPos(sf::Vector2f pos)
{
    if (pos.x > Util.getWidth())
    {
        pos.x = Util.getWidth();
    }
    if (pos.y > Util.getHeight())
    {
        pos.y = Util.getHeight();
    }

    ballPos = pos;
}

//Retourne le côté de la collision, pour une meilleure gestion des rebonds
sf::Vector2f Ball::isColliding()
{
    float offset = 2.f;

#pragma region Collisions écran
    //On check si la hauteur de la balle dépasse un des bords de la fenêtre
    if (ballPos.y + shape.getLocalBounds().height / 2 > Util.getHeight())
    {
        std::cout << "check" << std::endl;
        speed = 0;
        dir.x = 0;
        dir.y = 0;

        Util.setBlocked(false);
        
        //On replace la balle en gardant la position en x
        ballPos = sf::Vector2f(shape.getPosition().x, (Util.getHeight() - shape.getLocalBounds().height / 2));
    }
    else if (ballPos.y - shape.getLocalBounds().height / 2 < 0)
    {
        dir.y = -dir.y;
        ballPos = sf::Vector2f(shape.getPosition().x, shape.getPosition().y + 5);
    }

    //On check si la largeur de la balle dépasse la fenêtre
    if (ballPos.x + shape.getLocalBounds().width / 2 > Util.getWidth())
    {
        dir.x = -dir.x;
        ballPos = sf::Vector2f(shape.getPosition().x - 5, shape.getPosition().y);
    }
    else if (ballPos.x - shape.getLocalBounds().width / 2 < 0)
    {
        dir.x = -dir.x;
        ballPos = sf::Vector2f(shape.getPosition().x + 5, shape.getPosition().y);
    }
#pragma endregion

    return dir;
}

sf::Vector2f Ball::isCollidingWith(sf::Shape* other) 
{
    float offset = 2.f;

    if (shape.getGlobalBounds().intersects(other->getGlobalBounds()))
    {
        float distDroite = abs((shape.getGlobalBounds().left + shape.getGlobalBounds().width) - other->getGlobalBounds().left);
        float distGauche = abs(shape.getGlobalBounds().left - (other->getGlobalBounds().left + other->getGlobalBounds().width));
        float distBas = abs((shape.getGlobalBounds().top + shape.getGlobalBounds().height) - other->getGlobalBounds().top);
        float distHaut = abs(shape.getGlobalBounds().top - (other->getGlobalBounds().top + other->getGlobalBounds().height));

        //Si la balle tape sur la gauche de l'objet
        if (distGauche < distDroite && distGauche < distHaut && distGauche < distBas)
        {
            dir.x = -dir.x;
            //this.move(offset, 0);
        }
        //Si elle tape sur la droite
        else if (distDroite < distGauche && distDroite < distHaut && distDroite < distBas)
        {
            dir.x = -dir.x;
            //shape->move(-offset, 0);
        }
        //Si elle tape en haut
        else if (distHaut < distGauche && distHaut < distDroite && distHaut < distBas)
        {
            dir.y = -dir.y;
            //shape->move(0, offset);
        }
        //Et dans le dernier cas, collision en bas
        else
            dir.y = -dir.y;
        //shape->move(0, -offset);
    }

    //TODO delete la brique

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
