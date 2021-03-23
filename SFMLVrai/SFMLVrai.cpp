#include <iostream>
#include <SFML/Graphics.hpp>
#include "Utilities.h";

int main()
{
    Utilities Util;

    sf::RenderWindow window(sf::VideoMode(Util.WIDTH_W, Util.HEIGHT_W), "Cercle vert"); //On définit une taille de fenêtre de base en dur.
    sf::CircleShape shape(25.f); //On définit la taille du cercle
    shape.setFillColor(sf::Color::Red);

    Util.setShapeOrigine(&shape, 0.5, 0.5); //On set le point de pivot de la balle au milieu de l'axe X et en bas

    Util.setObjectPosition(&shape, Util.WIDTH_W / 2, Util.HEIGHT_W - shape.getLocalBounds().height/2); //On place la balle en bas de l'écran, quelle que soit sa taille.


    while (window.isOpen())
    {
        sf::Vector2f speed(0, 0);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (Util.isColliding(&shape))
            {
                speed.y = -1;
            }
        }

        shape.setPosition(shape.getPosition() + speed);

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}