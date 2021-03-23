#pragma once

#include <SFML/Graphics.hpp>

class Utilities
{
	public :
		float WIDTH_W = 1280;
		float HEIGHT_W = 720;

		void setShapeOrigine(sf::Shape* shape, float x, float y);

		void setObjectPosition(sf::Shape* shape, int x, int y);

		bool isColliding(sf::Shape* shape);
};

