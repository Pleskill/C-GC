#pragma once

#include <SFML/Graphics.hpp>

class Utilities
{
	public :
		float WIDTH = 1280;
		float HEIGHT = 720;

		void setShapeOrigine(sf::Shape* forme, float x, float y);

		void setObjectPosition(sf::Shape* forme, int x, int y);

		bool isColliding(sf::Shape* forme, sf::Vector2f* vitesse);
};

