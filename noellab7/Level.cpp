#include "Level.h"
#include <iostream>
void Level::setup()
{
	reset = false;
	if (!tex.loadFromFile("ASSETS/IMAGES/spike.png"))
	{
		std::cout << "FAILED TO LOAD FILE\n";
	}
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			if (levelData[row][col] == 1)
			{
				shape[row][col].setTexture(&tex);
				shape[row][col].setSize(sf::Vector2f(40.f,40.f));
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
			if (levelData[row][col] == 1)
			{
				window.draw(shape[row][col]);
			}
		}
	}
}
