#include <iostream>
#include <SFML/Graphics.hpp>
#include "Utilities.h";

int main()
{
    Utilities Util;

    sf::RenderWindow window(sf::VideoMode(Util.WIDTH, Util.HEIGHT), "Cercle vert"); //On définit une taille de fenêtre de base en dur.
    sf::CircleShape shape(25.f); //On définit la taille du cercle
    shape.setFillColor(sf::Color::Red);

    Util.setShapeOrigine(&shape, 0.5, 1); //On set le point de pivot de la balle au milieu de l'axe X et en bas

    Util.setObjectPosition(&shape, Util.WIDTH / 2, Util.HEIGHT); //On place la balle en bas de l'écran, quelle que soit sa taille.


    while (window.isOpen())
    {
        sf::Vector2f vite(0, 0);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                vite.y = -1;
            }
            else
            {
                vite.y = 0;
            }
        }

        shape.setPosition(shape.getPosition() + vite);

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}