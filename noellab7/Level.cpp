#include "Level.h"
#include <iostream>
void Level::setup()
{
	reset = false;
	texBlock.loadFromFile("ASSETS/IMAGES/block.png");
	texSpike.loadFromFile("ASSETS/IMAGES/spike.png");
	texFlag.loadFromFile("ASSETS/IMAGES/flag.png");
	texBounce.loadFromFile("ASSETS/IMAGES/bounce.png");
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			if (levelData[row][col] == 1) shape[row][col].setTexture(&texBlock);
			if (levelData[row][col] == 2) shape[row][col].setTexture(&texSpike);
			if (levelData[row][col] == 3) shape[row][col].setTexture(&texFlag);
			if (levelData[row][col] == 4) shape[row][col].setTexture(&texBounce);
			if (levelData[row][col] > 0)
			{
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
