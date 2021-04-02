#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include "Entity.h"

class LevelManager
{
public:
	void readFile();

	std::vector<std::string> getLevel();

	void destroyAll();

	std::list<Brick> bricksList;

private:
	std::vector<std::string> level;

	int nbLignes = 5;
};