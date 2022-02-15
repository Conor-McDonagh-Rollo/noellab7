#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"

class Player
{
private:
	sf::Texture tex;
	sf::Sprite body;
	bool grounded = true;
	sf::Vector2f vel;
	
public:
	void Setup();
	void Draw(sf::RenderWindow& window);
	void Update(Level& l);
	void ProcessKeys();
	sf::FloatRect GetBounds() { return body.getGlobalBounds(); }
	sf::Vector2f GetPosition() { return body.getPosition(); }

	bool dead = false;
	bool win = false;
};

