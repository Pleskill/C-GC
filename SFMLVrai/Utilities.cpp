#include "Utilities.h"
#include <math.h>

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

//Retourne le c�t� de la collision, puis une meilleure gestion des rebonds
int Utilities::isColliding(sf::Shape* shape)
{
    int side = 0; //On d�finit une chaine de caract�re qui nous dit ou la collision avec la balle � lieu

    //On check si la hauteur de la balle d�passe un des bords de la fen�tre
    if (shape->getPosition().y + shape->getLocalBounds().height / 2 > HEIGHT_W)
    {
        side = 2;

        shape->setPosition(startPos); //TODO si la balle sors par en dessous de l'�cran, elle ne rebondit pas
        blocked = false;
    }
    else if (shape->getPosition().y - shape->getLocalBounds().height / 2 < 0)
    {
        side = 1;
        shape->setPosition(shape->getPosition().x, shape->getPosition().y + 5);
    }

    //On check si la largeur de la balle d�passe la fen�tre
    if (shape->getPosition().x + shape->getLocalBounds().width / 2 > WIDTH_W)
    {
        side = 3;
        shape->setPosition(shape->getPosition().x - 5, shape->getPosition().y);
    }
    else if(shape->getPosition().x - shape->getLocalBounds().width / 2 < 0)
    {
        side = 4;
        shape->setPosition(shape->getPosition().x + 5, shape->getPosition().y);
    }
    return side;
}

void Utilities::windowSetup() 
{
   window = new sf::RenderWindow(sf::VideoMode(WIDTH_W, HEIGHT_W), "Cercle vert"); //On d�finit une taille de fen�tre de base en dur.
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