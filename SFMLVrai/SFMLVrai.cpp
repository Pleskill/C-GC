#include <iostream>
#include <SFML/Graphics.hpp>
#include "Utilities.h";

int main()
{
    Utilities Util;

    Util.windowSetup();

    sf::CircleShape shape(25.f); //On d�finit la taille du cercle
    shape.setFillColor(sf::Color::Red);

    sf::Vector2f startPosition(Util.WIDTH_W / 2, Util.HEIGHT_W / 2);

    Util.setShapeOrigine(&shape, 0.5, 0.5); //On set le point de pivot de la balle au milieu de l'axe X et en bas

    Util.setObjectPosition(&shape, startPosition); //On place la balle en bas de l'�cran, quelle que soit sa taille.

    sf::Clock oClock;

    sf::Vector2f speed(0, 0); //Initialisation avec vitesse n�gative parce que �a part vers le haut

    while (Util.getWindow()->isOpen())
    {
        float deltaTime = oClock.getElapsedTime().asSeconds();
        oClock.restart();

        sf::Event event;
        while (Util.getWindow()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Util.getWindow()->close();
        }

        //Si on clique
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            //On lit la position locale de la souris (relativement � une fen�tre)
            sf::Vector2i localPosition = sf::Mouse::getPosition(*Util.getWindow()); // window est un sf::Window et pas un sf::RenderWindow

            //On r�cup�re le vecteur entre la position du centre de la balle et la souris et on le normalise (oui �a fait beaucoup)
            Util.normalize(Util.getVectorBtw(shape.getPosition(), sf::Vector2f(localPosition)));

            speed.y = -300; //Quand on clique �a lance la vitesse
            speed.x = 300;
            //Util.blocked = true;
        }

        //En fonction du renvoi de la fonction, on applique un caract�re � la balle
        switch (Util.isColliding(&shape))
        {
            case 1:
                speed.y = -speed.y;
                break;
            case 2:
                speed.y = 0;
                speed.x = 0;
                shape.setPosition(startPosition);
                break;
            case 3:
                speed.x = -speed.x;
                break;
            case 4:
                speed.x = -speed.x;
                break;
            default:
                break;
        }

        shape.setPosition(shape.getPosition() + speed * deltaTime);

        Util.getWindow()->clear();
        Util.getWindow()->draw(shape);
        Util.getWindow()->display();

        //std::cout << deltaTime << std::endl;
    }

    return 0;
}
