#include "Utilities.h"
#include <math.h>

bool Utilities::blocked = false;

void Utilities::setShapeOrigine(sf::Shape* shape, float x, float y)
{
    shape->setOrigin(shape->getLocalBounds().width * x, shape->getLocalBounds().height * y);
}

void Utilities::windowSetup() 
{
   window = new sf::RenderWindow(sf::VideoMode(WIDTH_W, HEIGHT_W), "Cercle vert"); //On définit une taille de fenêtre de base en dur.
}

sf::RenderWindow* Utilities::getWindow()
{
    return window;
}

sf::Vector2f Utilities::getVectorBtw(sf::Vector2f posObj1, sf::Vector2f posObj2)
{
    sf::Vector2f dir(posObj2.x - posObj1.x, posObj2.y - posObj1.y);
    return dir;
}

sf::Vector2f Utilities::normalize(sf::Vector2f vect)
{
    float norme = sqrt(vect.x * vect.x + vect.y * vect.y);

    return sf::Vector2f(vect.x / norme, vect.y / norme);
}

float Utilities::getWidth()
{
    return WIDTH_W;
}

float Utilities::getHeight()
{
    return HEIGHT_W;
}

bool Utilities::getBlocked()
{
    return blocked;
}

void Utilities::setBlocked(bool b)
{
    blocked = b;
}