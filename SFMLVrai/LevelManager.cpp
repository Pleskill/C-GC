#include <iostream>
#include "LevelManager.h"
#include "Entity.h"
#include <fstream>

void LevelManager::readFile()
{
	std::ifstream inFile;

    int i = 0;

	inFile.open("D:\Documents\LevelBuilder.txt");

    if (inFile.is_open()) 
    {
        std::string line;

        //Stock le contenu des 5 premières lignes dans un vecteur
        while (std::getline(inFile, line) && i < nbLignes) 
        {
            // using printf() in all tests for consistency
            std::cout << line.c_str();

            level.push_back(line);
            i++;
        }
        inFile.close();
    }
}

std::vector<std::string> LevelManager::getLevel()
{
    return level;
}

void LevelManager::destroyAll()
{
    for (std::list<Brick>::iterator it = bricksList.begin(); it != bricksList.end(); it++)
    {
        if ((*it).getKC())
        {
            delete &(*it);
            break;
        }
    }
}
