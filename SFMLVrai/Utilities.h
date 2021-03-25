#pragma once

#include <SFML/Graphics.hpp>

class Utilities
{
public:
    float WIDTH_W = 1280;
    float HEIGHT_W = 720;

    bool blocked = false;

    sf::RenderWindow* window;

    void setShapeOrigine(sf::Shape* shape, float x, float y);

    void setObjectPosition(sf::Shape* shape, sf::Vector2f);

    int isColliding(sf::Shape* shape);

    void windowSetup();

    sf::RenderWindow* getWindow();

    sf::Vector2f getVectorBtw(sf::Vector2f posObj1, sf::Vector2f posObj2);

    sf::Vector2f normalize(sf::Vector2f vect);
};
