#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "Lab 6" },
	m_exitGame{ false }, //when true game will exit
	level{ m_window }
{
	state = gameState::LevelEditor;
	setup(); // load texture
	view.setSize(sf::Vector2f(800.f, 600.f));
	bg.setOrigin(400.f,300.f);
	editorOffset = sf::Vector2f(360, 540);
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

		switch (state)
		{
		case gameState::Game:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				setup();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
			{
				state = gameState::LevelEditor;
			}
			player.ProcessKeys();
			break;
		case gameState::LevelEditor:
			if (sf::Event::MouseWheelScrolled == newEvent.type)
			{
				if (sf::Mouse::VerticalWheel == newEvent.mouseWheelScroll.wheel)
				{
					if (newEvent.mouseWheelScroll.delta == 1)
					{
						editorOffset.x += 50.f;
					}
					else if (newEvent.mouseWheelScroll.delta == -1)
					{
						editorOffset.x -= 50.f;
					}
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				state = gameState::Game;
			}
			if (sf::Event::KeyReleased == newEvent.type)
			{
				switch (newEvent.key.code)
				{
				case sf::Keyboard::Num1:
					level.currentLevel = 0;
					level.setup();
					break;
				case sf::Keyboard::Num2:
					level.currentLevel = 1;
					level.setup();
					break;
				case sf::Keyboard::Num3:
					level.currentLevel = 2;
					level.setup();
					break;
				case sf::Keyboard::Num4:
					level.currentLevel = 3;
					level.setup();
					break;
				case sf::Keyboard::Num5:
					level.currentLevel = 4;
					level.setup();
					break;
				case sf::Keyboard::Num6:
					level.currentLevel = 5;
					level.setup();
					break;
				case sf::Keyboard::Num7:
					level.currentLevel = 6;
					level.setup();
					break;
				case sf::Keyboard::Num8:
					level.currentLevel = 7;
					level.setup();
					break;
				case sf::Keyboard::Num9:
					level.currentLevel = 8;
					level.setup();
					break;
				}
			}
			break;
		}
		
	}
}

//time interval per frame
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	switch (state)
	{
	case gameState::Game:
		if (!player.win)
		{
			if (level.reset) setup();
			player.Update(level);
			view.setCenter(player.GetPosition().x, 300);
			if (player.dead)
			{
				setup();
			}
		}
		else
		{
			win.setPosition(view.getCenter() - sf::Vector2f(win.getGlobalBounds().width / 2, win.getGlobalBounds().height / 2));
		}
		break;

	case gameState::LevelEditor:
		view.setCenter(editorOffset.x, 300);
		level.LevelEditor();
		break;
	}

	if (view.getCenter().x < 360)
	{
		view.setCenter(360, 300);
		editorOffset.x = 360;
	}

	bg.setPosition(view.getCenter());
}

// draw the frame and then switch buffers
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.setView(view);

	m_window.draw(bg);

	switch (state)
	{
	case gameState::Game:
		level.draw();
		player.Draw(m_window);

		if (player.win)
		{
			m_window.draw(win);
		}
		break;

	case gameState::LevelEditor:
		level.draw();
		break;
	}

	m_window.display();
}

void Game::setup()
{
	bgtex.loadFromFile("ASSETS/IMAGES/bg.png");
	bg.setTexture(bgtex);
	wintex.loadFromFile("ASSETS/IMAGES/wintext.png");
	win.setTexture(wintex);
	level.setup();
	player.Setup();
}
