#pragma once

#include <SFML/Graphics.hpp>

class Brick
{
	public:
		float height = 50;
		float width = 100;

		sf::RectangleShape* brick;

	private:
		sf::Vector2f brickPos;

		//Relatif aux positions de la brique
		sf::Vector2f getBrickpos();

		void setBrickPos(sf::Vector2f pos);

		void createRectangle();
};

