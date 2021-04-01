#pragma once

#include <SFML/Graphics.hpp>
#include <list>

class Entity
{
public:
	virtual sf::Vector2f getPos() = 0;

	virtual void setPos(sf::Vector2f pos) = 0;
};

class Brick : public Entity
{
public:
	Brick(float h, float w);

	~Brick();

	//Relatif aux positions de la brique
	sf::Vector2f getPos();

	void setPos(sf::Vector2f pos);

	sf::RectangleShape shape;

	float getHeight();

	float getWidth();

	bool getKC();

	void setKC(bool b);

private:
	sf::Vector2f brickPos;

	bool KC;

	float height;
	float width;
};

class Ball : public Entity
{
public:
	Ball(sf::Vector2f d, float s);

	//Relatif aux positions de la brique
	sf::Vector2f getPos();

	void setPos(sf::Vector2f pos);

	sf::CircleShape shape;

	sf::Vector2f isColliding();

	sf::Vector2f isCollidingWith(Brick* other);

	sf::Vector2f getDir();

	void setDir(sf::Vector2f dir);

	float getSpeed();

	void setSpeed(float s);

private:
	sf::Vector2f ballPos;

	sf::Vector2f dir;

	float speed;
};

class Cannon : public Entity
{
public:
	Cannon();

	sf::RectangleShape shape;

	float getAngle();

	void setAngle(float f);

private:
	float angle;

	sf::Texture tex;
};