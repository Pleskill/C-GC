#pragma once

#include <SFML/Graphics.hpp>

class Utilities
{
public:
    float WIDTH_W = 1280;
    float HEIGHT_W = 720;

    bool blocked = false;

    void setShapeOrigine(sf::Shape* shape, float x, float y);

    void setObjectPosition(sf::Shape* shape, sf::Vector2f);

    bool isColliding(sf::Shape* shape);
};