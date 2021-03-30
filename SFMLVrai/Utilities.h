#pragma once

#include <SFML/Graphics.hpp>

class Utilities
{
public:
    sf::RenderWindow* window;

    void setShapeOrigine(sf::Shape* shape, float x, float y);

    void windowSetup();

    sf::RenderWindow* getWindow();

    sf::Vector2f getVectorBtw(sf::Vector2f posObj1, sf::Vector2f posObj2);

    sf::Vector2f normalize(sf::Vector2f vect);

    float getWidth();

    float getHeight();

    bool getBlocked();

    void setBlocked(bool b);

    static bool blocked;
    
private:
    float WIDTH_W = 1280;
    float HEIGHT_W = 720;
};
