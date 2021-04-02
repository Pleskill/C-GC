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
    Cannon Cannon(sf::Vector2f(0,0));
    LevelManager LM;
    ScoreManager SM;

    Util.setBlocked(false);

    for (int i = 0; i <= 4; i++)
    {
        //On les ajoute à la liste
        Brick* b = new Brick(50, 130);
        LM.bricksList.push_back(*b);
    }

    sf::Vector2f startBallPosition(Util.getWidth() / 2, (Util.getHeight() - Ball.shape.getLocalBounds().height / 2));
    sf::Vector2f startCanonPosition(Util.getWidth() / 2, (Util.getHeight() - Cannon.shape.getLocalBounds().height / 2));

    sf::Clock oClock;
#pragma endregion

#pragma region Start
    Util.windowSetup(); //On définit + récupère la fenêtre de jeu

    Util.setShapeOrigine(&Ball.shape, 0.5, 0.5); //On set le point de pivot de la balle au milieu de l'axe X et Y

    Ball.shape.setFillColor(sf::Color::Red); //Balle en rouge

    Ball.shape.setPosition(startBallPosition); //On place la balle en bas de l'écran, quelle que soit sa taille.

    Util.setShapeOrigine(&Cannon.shape, 0.5, 0.5); //On change l'origine du canon

    Cannon.shape.setPosition(startCanonPosition); //Puis sa position

    int compteur = 0;
    //Pour tous les blocs de la liste, on va leur donner une position
    for (std::list<Brick>::iterator it = LM.bricksList.begin(); it != LM.bricksList.end(); it++)
    {
        (*it).shape.setPosition(sf::Vector2f(100 * (compteur + 1) + 130 * compteur, 100));
        (*it).shape.setFillColor(sf::Color::Blue);
        compteur++;
    }

#pragma endregion

#pragma region Update
    while (Util.getWindow()->isOpen())
    {
        //Une floppée de vecteurs, utiles pour les calculs de rotation et le déplacement de la balle
        sf::Vector2f cannonForward = sf::Vector2f(1, 0);
        sf::Vector2f cannonForwardNorm = Util.normalize(cannonForward);
        sf::Vector2f souris = sf::Vector2f(sf::Mouse::getPosition(*Util.getWindow()));
        sf::Vector2f sourisNorm = Util.normalize(souris);

        //On fait tourner le canon en fonction de la souris
        Cannon.setAngle(Util.calculAngle(cannonForward, souris)); //--> marche pas

        if (souris.x < Util.getWidth() / 2)
        {
            Cannon.shape.setRotation(-Cannon.getAngle());
        }
        else
        {
            Cannon.shape.setRotation(Cannon.getAngle());
        }
        
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

            //On applique la direction de la souris sur la balla
            Ball.setDir(Util.CreateNormalizedVector(sf::Mouse::getPosition(*Util.getWindow()), Ball.getStartPos()));

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
        Util.getWindow()->draw(Cannon.shape);

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