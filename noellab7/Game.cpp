#include "Game.h"

Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "Lab 6" },
	m_exitGame{ false } //when true game will exit
{
	setup(); // load texture
	view.setSize(sf::Vector2f(800.f, 600.f));
	bg.setOrigin(400.f,300.f);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		player.ProcessKeys();
	}
}

//time interval per frame
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	if (level.reset) setup();
	player.Update(level);
	view.setCenter(player.GetPosition().x , 300);
	bg.setPosition(view.getCenter());
}

// draw the frame and then switch buffers
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.setView(view);

	m_window.draw(bg);
	level.draw(m_window);
	player.Draw(m_window);

	m_window.display();
}

void Game::setup()
{
	bgtex.loadFromFile("ASSETS/IMAGES/bg.png");
	bg.setTexture(bgtex);
	level.setup();
	player.Setup();
}
