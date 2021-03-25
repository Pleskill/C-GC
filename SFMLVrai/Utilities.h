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
};
