#include "Game.h"

#include <iostream>

#include "GUIButton.h"

Game::Game(void)
{
}


Game::~Game(void)
{
	
}

void Game::initialise(sf::Vector2u _screenSize, std::string _windowName)
{
	m_ScreenSize = _screenSize;
	
	
	m_View.setSize  ((float)(m_ScreenSize.x),			(float)(m_ScreenSize.y));
	m_View.setCenter((float)(m_ScreenSize.x / 2.0f),	(float)(m_ScreenSize.y / 2.0f));

	m_Window.create(sf::VideoMode(_screenSize.x, _screenSize.y), _windowName);

	m_FontManager.loadAllFonts();

	GUIFrame *newFrame = new GUIFrame(sf::FloatRect());

	m_ButtonTest = false;
	GUIButton *newButton = new GUIButton("Mark's Button", &m_ButtonTest, sf::Vector2f(100.0f, 100.0f), sf::Vector2f());

	newFrame->addObject(newButton);

	m_GUIManager.addFrame(newFrame);
		
	run();
}

void Game::run(void)
{
	m_Running = true;

	sf::Clock clock;
	while (m_Running)
	{
		sf::sleep(sf::milliseconds(15));

		m_GUIManager.update(clock.getElapsedTime());

		if (m_ButtonTest)
		{
			std::cout << "Yay!" << std::endl;
		}
		
		handleEvents();

		clock.restart();

		m_Window.clear();

		m_Window.draw(m_GUIManager);

		m_Window.display();
	}
}

void Game::handleEvents(void)
{
	sf::Event event;

	while (m_Window.pollEvent(event))
	{
		m_InputManager.handleEvent(event);
	}
}

void Game::buttonActivated(void)
{
	std::cout << "Button activated!" << std::endl;
}