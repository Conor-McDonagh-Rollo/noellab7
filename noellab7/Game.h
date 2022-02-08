#pragma once
#include "Level.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	void run();
private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	void setup();

	Level level;
	Player player;

	sf::Texture bgtex;
	sf::Sprite bg;

	sf::View view;

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game
};

