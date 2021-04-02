#include <iostream>
#include "Entity.h"
#include "Utilities.h"
#include <math.h>

Utilities Util;

Brick::Brick(float h, float w)
{
    height = h;
    width = w;
    shape.setSize(sf::Vector2f(w, h));
    KC = false;
}

Brick::~Brick()
{

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

bool Brick::getKC()
{
    return KC;
}

void Brick::setKC(bool b)
{
    KC = b;
}


Ball::Ball(sf::Vector2f d, float s)
{
    dir = d;
    speed = s;
    shape.setRadius(15.f);
    startPos = sf::Vector2f(Util.getWidth() / 2, (Util.getHeight() - shape.getLocalBounds().height / 2));
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
    if (shape.getPosition().y + shape.getLocalBounds().height / 2 > Util.getHeight())
    {
        std::cout << "check" << std::endl;
        speed = 0;
        dir.x = 0;
        dir.y = 0;

        Util.setBlocked(false);
        
        //On replace la balle en gardant la position en x
        shape.setPosition(startPos);
    }
    else if (shape.getPosition().y - shape.getLocalBounds().height / 2 < 0)
    {
        dir.y = -dir.y;
        shape.setPosition(sf::Vector2f(shape.getPosition().x, shape.getPosition().y + 5));
    }

    //On check si la largeur de la balle dépasse la fenêtre
    if (shape.getPosition().x + shape.getLocalBounds().width / 2 > Util.getWidth())
    {
        dir.x = -dir.x;
        shape.setPosition(sf::Vector2f(shape.getPosition().x - 5, shape.getPosition().y));
    }
    else if (shape.getPosition().x - shape.getLocalBounds().width / 2 < 0)
    {
        dir.x = -dir.x;
        shape.setPosition(sf::Vector2f(shape.getPosition().x + 5, shape.getPosition().y));
    }
#pragma endregion

    return dir;
}

sf::Vector2f Ball::isCollidingWith(Brick* other) 
{
    float offset = 2.f;

    if (shape.getGlobalBounds().intersects(other->shape.getGlobalBounds()))
    {
        float distDroite = abs((shape.getGlobalBounds().left + shape.getGlobalBounds().width) - other->shape.getGlobalBounds().left);
        float distGauche = abs(shape.getGlobalBounds().left - (other->shape.getGlobalBounds().left + other->shape.getGlobalBounds().width));
        float distBas = abs((shape.getGlobalBounds().top + shape.getGlobalBounds().height) - other->shape.getGlobalBounds().top);
        float distHaut = abs(shape.getGlobalBounds().top - (other->shape.getGlobalBounds().top + other->shape.getGlobalBounds().height));

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

        other->setKC(true);
    }
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

sf::Vector2f Ball::getStartPos()
{
    return startPos;
}

Cannon::Cannon(sf::Vector2f p)
{
    pos = p;
    angle = 0;
    shape.setSize(sf::Vector2f(48, 60));
    tex.loadFromFile("Ressource/cannon.png");
    shape.setTexture(&tex);
}

float Cannon::getAngle()
{
    return angle;
}

sf::Vector2f Cannon::getPos()
{
    return pos;
}

void Cannon::setAngle(float f)
{
    angle = f;
}

void Cannon::setPos(sf::Vector2f p)
{
    pos = p;
}
