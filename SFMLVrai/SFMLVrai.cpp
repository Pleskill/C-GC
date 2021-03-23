#include <iostream>
#include <SFML/Graphics.hpp>
#include "Utilities.h";

int main()
{
    Utilities Util;

    sf::RenderWindow window(sf::VideoMode(Util.WIDTH_W, Util.HEIGHT_W), "Cercle vert"); //On d�finit une taille de fen�tre de base en dur.
    sf::CircleShape shape(25.f); //On d�finit la taille du cercle
    shape.setFillColor(sf::Color::Red);

    sf::Vector2f startPosition(Util.WIDTH_W / 2, Util.HEIGHT_W / 2);

    Util.setShapeOrigine(&shape, 0.5, 0.5); //On set le point de pivot de la balle au milieu de l'axe X et en bas

    Util.setObjectPosition(&shape, startPosition); //On place la balle en bas de l'�cran, quelle que soit sa taille.

    sf::Clock oClock;

    sf::Vector2f speed(0, 0); //Initialisation avec vitesse n�gative parce que �a part vers le haut

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

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !Util.blocked)
        {
            speed.y = -300; //Quand on clique �a lance la vitesse
            Util.blocked = true;
        }

        if (Util.isColliding(&shape))
        {
            speed.y = -speed.y; //Th�oriquement, si on touche un bord, on inverse la vitesse
        }

        shape.setPosition(shape.getPosition() + speed * deltaTime);

        window.clear();
        window.draw(shape);
        window.display();

        std::cout << deltaTime << std::endl;
    }

    return 0;
}
