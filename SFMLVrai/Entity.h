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

	sf::Vector2f isColliding(sf::Shape* shape);

	sf::Vector2f isCollidingWith(sf::Shape* shape, sf::Shape* other);

	sf::Vector2f getDir();

	void setDir(sf::Vector2f dir);

	float getSpeed();

	void setSpeed(float s);

private:
	sf::Vector2f ballPos;

	sf::Vector2f dir;

	float speed;
};