#include "Player.h"

void Player::Setup()
{
	tex.loadFromFile("ASSETS/IMAGES/player.png");
	body.setTexture(tex);
	body.setPosition(360, 540);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::Update(Level& l)
{
	if (left) body.move(-5, 0);
	if (right) body.move(5, 0);
	
	if (!grounded)
	{
		body.move(vel);
		vel.y += 0.5f;
		if (body.getPosition().y >= 545)
		{
			body.setPosition(body.getPosition().x, 545);
			grounded = true;
		}
	}

	sf::FloatRect below(sf::Vector2f(body.getPosition().x, body.getPosition().y + body.getGlobalBounds().height),
		sf::Vector2f(body.getGlobalBounds().width, -1));
	sf::FloatRect above;
	sf::FloatRect right;
	sf::FloatRect left;
	for (int row = 0; row < l.numRows; row++)
	{
		for (int col = 0; col < l.numCols; col++)
		{
			if (l.levelData[row][col] == 1)
			{
				if (below.intersects(l.shape[row][col].getGlobalBounds()))
				{
					grounded = true;
					body.setPosition(body.getPosition().x, l.shape[row][col].getPosition().y - body.getGlobalBounds().height);
				}
			}
		}
	}
}

void Player::ProcessKeys()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		left = true;
	}
	else
	{
		left = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		right = true;
	}
	else
	{
		right = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && grounded)
	{
		grounded = false;
		vel.y = -10.f;
	}
}
