#include "Player.h"
#include <iostream>

void Player::Setup()
{
	tex.loadFromFile("ASSETS/IMAGES/player.png");
	body.setTexture(tex);
	body.setPosition(360, 540);
	dead = false;
	win = false;
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::Update(Level& l)
{
	
	if (!grounded)
	{
		body.move(0, vel.y);
		vel.y += 0.5f;
		if (body.getPosition().y >= 545)
		{
			body.setPosition(body.getPosition().x, 545);
			grounded = true;
			vel.y = 0;
		}
	}

	sf::FloatRect below(sf::Vector2f(body.getPosition().x, body.getPosition().y + body.getGlobalBounds().height),
		sf::Vector2f(body.getGlobalBounds().width, 5));
	sf::FloatRect above(body.getPosition() - sf::Vector2f(0,5),
		sf::Vector2f(body.getGlobalBounds().width, 5));
	sf::FloatRect right(sf::Vector2f(body.getPosition().x + body.getGlobalBounds().width, body.getPosition().y + 2),
		sf::Vector2f(1,body.getGlobalBounds().height - 4));
	sf::FloatRect left(sf::Vector2f(body.getPosition().x - 5, body.getPosition().y + 2),
		sf::Vector2f(1, body.getGlobalBounds().height - 4));
	for (int row = 0; row < l.numRows; row++)
	{
		for (int col = 0; col < l.numCols; col++)
		{
			if (l.levelData[row][col] == 1)
			{
				if (above.intersects(l.shape[row][col].getGlobalBounds()))
				{
					if (vel.y < 0) vel.y = 0;
				}
				if (right.intersects(l.shape[row][col].getGlobalBounds()))
				{
					if (vel.x > 0) vel.x = 0;
				}
				if (left.intersects(l.shape[row][col].getGlobalBounds()))
				{
					if (vel.x < 0) vel.x = 0;
				}
				//GROUND CHECKS
				if (!below.intersects(l.shape[l.lastIntersectedRow][l.lastIntersectedColumn].getGlobalBounds()) && body.getPosition().y < 545)
				{
					grounded = false;
				}
				if (below.intersects(l.shape[row][col].getGlobalBounds()))
				{
					grounded = true;
					vel.y = 0;
					body.setPosition(body.getPosition().x, l.shape[row][col].getPosition().y - body.getGlobalBounds().height);
					l.lastIntersectedRow = row;
					l.lastIntersectedColumn = col;
				}
			}
			else if (l.levelData[row][col] == 2)
			{
				if (below.intersects(l.shape[row][col].getGlobalBounds()) && vel.y > 0)
				{
					dead = true;
				}
			}
			else if (l.levelData[row][col] == 3)
			{
				if (body.getGlobalBounds().intersects(l.shape[row][col].getGlobalBounds()))
				{
					win = true;
				}
			}
			else if (l.levelData[row][col] == 4)
			{
				if (below.intersects(l.shape[row][col].getGlobalBounds()) && vel.y > 0)
				{
					vel.y *= -1.25f;
				}
			}
			
		}
	}

	body.move(vel.x, 0);
}

void Player::ProcessKeys()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		vel.x = -5;
	}
	else
	{
		if (vel.x == -5) vel.x = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		vel.x = 5;
	}
	else
	{
		if (vel.x == 5) vel.x = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && grounded)
	{
		grounded = false;
		vel.y = -10.f;
	}
}
