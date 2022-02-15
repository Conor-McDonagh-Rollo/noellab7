#include "Level.h"
#include <iostream>
void Level::setup()
{
	reset = false;
	if (!texBlock.loadFromFile("ASSETS/IMAGES/block.png"))
	{
		std::cout << "FAILED TO LOAD FILE\n";
	}
	if (!texSpike.loadFromFile("ASSETS/IMAGES/spike.png"))
	{
		std::cout << "FAILED TO LOAD FILE\n";
	}
	if (!texFlag.loadFromFile("ASSETS/IMAGES/flag.png"))
	{
		std::cout << "FAILED TO LOAD FILE\n";
	}
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			if (levelData[row][col] == 1)
			{
				shape[row][col].setTexture(&texBlock);
				shape[row][col].setSize(sf::Vector2f(40.f,40.f));
				shape[row][col].setPosition(row * 40, col * 40);
			}
			if (levelData[row][col] == 2)
			{
				shape[row][col].setTexture(&texSpike);
				shape[row][col].setSize(sf::Vector2f(40.f, 40.f));
				shape[row][col].setPosition(row * 40, col * 40);
			}
			if (levelData[row][col] == 3)
			{
				shape[row][col].setTexture(&texFlag);
				shape[row][col].setSize(sf::Vector2f(40.f, 40.f));
				shape[row][col].setPosition(row * 40, col * 40);
			}
		}
	}
}

void Level::draw(sf::RenderWindow& window)
{
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			if (levelData[row][col] > 0)
			{
				window.draw(shape[row][col]);
			}
		}
	}
}
