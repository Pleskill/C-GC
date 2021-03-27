#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
public:
	virtual void create() = 0;

	virtual sf::Vector2f getPos() = 0;

	virtual void setPos(sf::Shape* prop, sf::Vector2f pos) = 0;
};

class Brick : public Entity
{
public:
	float height = 50;
	float width = 100;

	void create();

	//Relatif aux positions de la brique
	sf::Vector2f getPos();

	void setPos(sf::Shape* prop, sf::Vector2f pos);

	sf::RectangleShape* brick;

private:
	sf::Vector2f brickPos;
};

class Ball : public Entity
{
public:
	void create();

	//Relatif aux positions de la brique
	sf::Vector2f getPos();

	void setPos(sf::Shape* prop, sf::Vector2f pos);

	sf::CircleShape* ball;

private:
	sf::Vector2f ballPos;
};