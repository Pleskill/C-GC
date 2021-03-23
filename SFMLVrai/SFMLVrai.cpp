#include <iostream>
#include <SFML/Graphics.hpp>
#include "Utilities.h";

int main()
{
    Utilities Util;

    sf::RenderWindow window(sf::VideoMode(1000, 500), "Cercle vert"); //On définit une taille de fenêtre de base en dur.
    sf::CircleShape shape(100.f); //On définit la taille du cercle
    shape.setFillColor(sf::Color::Red);

    Util.setShapeOrigine(&shape, 0.5, 1);

    shape.setPosition(window.getSize().x / 2, window.getSize().y);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}