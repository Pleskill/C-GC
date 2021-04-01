#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include "Utilities.h";
#include "Entity.h";
#include "LevelManager.h"
#include "ScoreManager.h"


int main()
{
#pragma region Variables
    Utilities Util;
    Ball Ball(sf::Vector2f(0, 0), 0);
    Cannon Cannon();
    LevelManager LM;
    ScoreManager SM;

    Util.setBlocked(false);
  


    for (int i = 0; i <= 4; i++)
    {
        //On les ajoute à la liste
        Brick* b = new Brick(50, 130);
        LM.bricksList.push_back(*b);
    }

    sf::Vector2f startPosition(Util.getWidth() / 2, (Util.getHeight() - Ball.shape.getLocalBounds().height / 2));

    sf::Clock oClock;
#pragma endregion

#pragma region Start


    Util.windowSetup(); //On définit + récupère la fenêtre de jeu

    Util.setShapeOrigine(&Ball.shape, 0.5, 0.5); //On set le point de pivot de la balle au milieu de l'axe X et Y

    Ball.shape.setFillColor(sf::Color::Red); //Balle en rouge

    Ball.shape.setPosition(startPosition); //On place la balle en bas de l'écran, quelle que soit sa taille.

    int compteur = 0;
    //Pour tous les blocs de la liste, on va leur donner une position
    for (std::list<Brick>::iterator it = LM.bricksList.begin(); it != LM.bricksList.end(); it++)
    {
        (*it).shape.setPosition(sf::Vector2f(100 * (compteur + 1) + 130 * compteur, 100));
        (*it).shape.setFillColor(sf::Color::Blue);
        compteur++;
    }

    /*LM.readFile();

    for (int i = 0; i < LM.getLevel().size(); i++)
    {
        std::cout << LM.getLevel()[i] << std::endl;
    }*/

#pragma endregion

#pragma region Update
    while (Util.getWindow()->isOpen())
    {
        //Mise en place du deltaTime
        float deltaTime = oClock.getElapsedTime().asSeconds();
        oClock.restart();

        //Evenement de fenêtre de base (fermeture)
        sf::Event event;
        while (Util.getWindow()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Util.getWindow()->close();
        }

        //Si on clique
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !Util.getBlocked())
        {
            Ball.setSpeed(500.f);

            //On lit la position locale de la souris (relativement à une fenêtre)
            sf::Vector2i localPosition = sf::Mouse::getPosition(*Util.getWindow()); //window est un sf::Window et pas un sf::RenderWindow

            //On récupère le vecteur entre la position du centre de la balle et la souris et on le normalise (oui ça fait beaucoup)
            Ball.setDir(Util.normalize(Util.getVectorBtw(Ball.shape.getPosition(), sf::Vector2f(localPosition))));
            Util.setBlocked(true);
        }

        //On check si ça touche les bords de l'écran
        Ball.setDir(Ball.isColliding());

        compteur = 0;

        //En fonction du renvoi de la fonction, on change sa direction. Ca cherche pour toutes les briques si la balle collide avec ou pas... a chaque frame
        for (std::list<Brick>::iterator it = LM.bricksList.begin(); it != LM.bricksList.end(); it++)
        {
            Ball.setDir(Ball.isCollidingWith(&(*it)));

            compteur++;
        }

        //Si la vitesse est égale à 0, le calcul de position va être = 0, et le rond va rester bloqué en haut à gauche
        if (Ball.getSpeed() != 0)
        {
            //Pour bouger, on ajoute à la postition la direction, qu'on multiplie par la vitesse et le deltaTime.
            Ball.shape.setPosition(Ball.shape.getPosition() + Ball.getDir() * Ball.getSpeed() * deltaTime);
        }

        Util.getWindow()->clear();
        Util.getWindow()->draw(Ball.shape);

        //Dessin de chaque éléments de la liste de blocs
        for (std::list<Brick>::iterator it = LM.bricksList.begin(); it != LM.bricksList.end(); it++)
        {
            if (!(*it).getKC())
            {
                Util.getWindow()->draw((*it).shape);
            }
            else
            {
                SM.addScore(1);
                std::cout << SM.score << std::endl;
                LM.bricksList.erase(it);
                break;
            }
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
//      l.erase(it); --> renvoie le prochain itératteur
// }
// it++