#include <iostream>
#include <SFML/Graphics.hpp>
#include "Utilities.h";
#include "Entity.h";

int main()
{
#pragma region Variables
    Utilities Util;
    Ball Ball;
    Brick Brick;

    //Cr�ation de balle et association a une variable
    Ball.create();
    sf::CircleShape shape = *Ball.ball;

    //Cr�ation de brique et association a une variable
    Brick.create();
    sf::RectangleShape bloc = *Brick.brick;

    sf::Vector2f startPosition(Util.WIDTH_W / 2, Util.HEIGHT_W - shape.getLocalBounds().height /2);

    sf::Clock oClock;

    float speed = 0; //Initialisation de la vitesse

    sf::Vector2f dir(0, 0); //On stocke la direction de chaque clicks
#pragma endregion

#pragma region Start
    Util.windowSetup(); //On d�finit + r�cup�re la fen�tre de jeu

    shape.setFillColor(sf::Color::Red); //Balle en rouge

    Util.setShapeOrigine(&shape, 0.5, 0.5); //On set le point de pivot de la balle au milieu de l'axe X et Y

    Ball.setPos(&shape, startPosition); //On place la balle en bas de l'�cran, quelle que soit sa taille.
    Brick.setPos(&bloc, sf::Vector2f(100, 100)); //On place une brique sur l'�cran pour les tests
#pragma endregion

#pragma region Update
    while (Util.getWindow()->isOpen())
    {
        //Mise en place du deltaTime
        float deltaTime = oClock.getElapsedTime().asSeconds();
        oClock.restart();

        //Evenement de fen�tre de base (fermeture)
        sf::Event event;
        while (Util.getWindow()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Util.getWindow()->close();
        }

        //Si on clique
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !Util.blocked)
        {
            speed = 500;

            //On lit la position locale de la souris (relativement � une fen�tre)
            sf::Vector2i localPosition = sf::Mouse::getPosition(*Util.getWindow()); //window est un sf::Window et pas un sf::RenderWindow

            //On r�cup�re le vecteur entre la position du centre de la balle et la souris et on le normalise (oui �a fait beaucoup)
            dir = Util.normalize(Util.getVectorBtw(shape.getPosition(), sf::Vector2f(localPosition)));
            Util.blocked = true;
        }

        //En fonction du renvoi de la fonction, on change sa direction
        switch (Ball.isColliding(&shape, &bloc))
        {
        case 1:
            dir.y = -dir.y;
            break;
        case 2:
            dir.y = 0;
            dir.x = 0;
            speed = 0;
            shape.setPosition(startPosition);
            Util.blocked = false;
            break;
        case 3:
            dir.x = -dir.x;
            break;
        case 4:
            dir.x = -dir.x;
            break;
        default:
            break;
        }

        //Si la vitesse est �gale � 0, le calcul de position va �tre = 0, et le rond va rester bloqu� en haut � gauche
        if (speed != 0)
        {
            //Pour bouger, on ajoute � la postition la direction, qu'on multiplie par la vitesse et le deltaTime.
            shape.setPosition(shape.getPosition() + dir * speed * deltaTime);
        }

        Util.getWindow()->clear();
        Util.getWindow()->draw(shape);
        Util.getWindow()->draw(bloc);
        Util.getWindow()->display();
    }
#pragma endregion

    return 0;
}
