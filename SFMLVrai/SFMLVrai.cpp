#include <iostream>
#include <SFML/Graphics.hpp>
#include "Utilities.h";

int main()
{
    Utilities Util;

    sf::RenderWindow window(sf::VideoMode(Util.WIDTH_W, Util.HEIGHT_W), "Cercle vert"); //On définit une taille de fenêtre de base en dur.
    sf::CircleShape shape(25.f); //On définit la taille du cercle
    shape.setFillColor(sf::Color::Red);

    sf::Vector2f startPosition(Util.WIDTH_W / 2, Util.HEIGHT_W / 2);

    Util.setShapeOrigine(&shape, 0.5, 0.5); //On set le point de pivot de la balle au milieu de l'axe X et en bas

    Util.setObjectPosition(&shape, startPosition); //On place la balle en bas de l'écran, quelle que soit sa taille.

    sf::Clock oClock;

    sf::Vector2f speed(0, 0); //Initialisation avec vitesse négative parce que ça part vers le haut

    while (window.isOpen())
    {
        float deltaTime = oClock.getElapsedTime().asSeconds();
        oClock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //Si on clique et que blocked est faux, donc que la balle n'est pas bloquée
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            speed.y = -300; //Quand on clique ça lance la vitesse
            //speed.x = 100;
            Util.blocked = true;
        }

        //En fonction du renvoi de la fonction, on applique un caractère à la balle
        switch (Util.isColliding(&shape))
        {
            case 1:
                speed.y = -speed.y;
                break;
            case 2:
                speed.y = 0;
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

        window.clear();
        window.draw(shape);
        window.display();

        std::cout << deltaTime << std::endl;
    }

    return 0;
}
