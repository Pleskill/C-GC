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

    std::vector<sf::RectangleShape> listBlocs;

    Util.setBlocked(false);

    for (int i = 0; i <= 4; i++)
    {
        //Cr�ation de briques
        Brick.create();
        sf::RectangleShape bloc = *Brick.brick;

        //On les ajoute � la liste
        listBlocs.push_back(bloc);
    }

    sf::Vector2f startPosition(Util.getWidth() / 2, Util.getHeight() - shape.getLocalBounds().height /2);

    sf::Clock oClock;
#pragma endregion

#pragma region Start
    Util.windowSetup(); //On d�finit + r�cup�re la fen�tre de jeu

    shape.setFillColor(sf::Color::Red); //Balle en rouge

    Util.setShapeOrigine(&shape, 0.5, 0.5); //On set le point de pivot de la balle au milieu de l'axe X et Y

    Ball.setPos(&shape, startPosition); //On place la balle en bas de l'�cran, quelle que soit sa taille.

    //Pour tous les blocs de la liste, on va leur donner une position
    for (int i = 0; i <= listBlocs.size() - 1; i++)
    {
        Brick.setPos(&listBlocs[i], sf::Vector2f(100*(i+1) + 130*i, 100));
    }

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
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !Util.getBlocked())
        {
            Ball.setSpeed(500);

            //On lit la position locale de la souris (relativement � une fen�tre)
            sf::Vector2i localPosition = sf::Mouse::getPosition(*Util.getWindow()); //window est un sf::Window et pas un sf::RenderWindow

            //On r�cup�re le vecteur entre la position du centre de la balle et la souris et on le normalise (oui �a fait beaucoup)
            Ball.setDir(Util.normalize(Util.getVectorBtw(shape.getPosition(), sf::Vector2f(localPosition))));
            Util.setBlocked(true);
        }

        //On check si �a touche les bords de l'�cran
        Ball.setDir(Ball.isColliding(&shape));

        //En fonction du renvoi de la fonction, on change sa direction
        for (int i = 0; i <= listBlocs.size() - 1; i++)
        {
            Ball.setDir(Ball.isCollidingWith(&shape, &listBlocs[i]));
        }

        //Si la vitesse est �gale � 0, le calcul de position va �tre = 0, et le rond va rester bloqu� en haut � gauche
        if (Ball.getSpeed() != 0)
        {
            //Pour bouger, on ajoute � la postition la direction, qu'on multiplie par la vitesse et le deltaTime.
            shape.setPosition(shape.getPosition() + Ball.getDir() * Ball.getSpeed() * deltaTime);
        }

        Util.getWindow()->clear();
        Util.getWindow()->draw(shape);

        //Dessin de chaque �l�ments de la liste de blocs
        for (int i = 0; i <= listBlocs.size() - 1; i++)
        {
            Util.getWindow()->draw(listBlocs[i]);
        }

        Util.getWindow()->display();
    }
#pragma endregion

    return 0;
}

// Iterator
// for(std::list<list> iterrator it = l.begin(), it != l.end(), it++)

//Et pour le while :
//auto it = l.begin()
// while(it != l.end)
// {
//      l.erase(it); --> renvoie le prochain it�ratteur
// }
// it++