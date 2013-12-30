#include "Game.h"

#include <ctime>
#include <cstdlib>


Game::Game(void)
{
}


Game::~Game(void)
{
	m_FontManager.unloadAllFonts();
	m_TextureManager.unloadAllTextures();
}

void Game::initialise(sf::Vector2u _screenSize, std::string _windowName)
{
	srand((unsigned int)time(nullptr));

	m_ScreenSize = _screenSize;
	
	m_View.setSize  ((float)(m_ScreenSize.x),			(float)(m_ScreenSize.y));
	m_View.setCenter((float)(m_ScreenSize.x / 2.0f),	(float)(m_ScreenSize.y / 2.0f));

	m_Window.create(sf::VideoMode(_screenSize.x, _screenSize.y), _windowName);

	m_FontManager.loadAllFonts();
	m_TextureManager.loadAllTextures();

	m_InputManager.registerGUIManager(&sGUIMANAGER);

	sGUIMANAGER.linkWindow(&m_Window);
	sGUIMANAGER.linkFontManager(&m_FontManager);
	sGUIMANAGER.linkInputManager(&m_InputManager);

	
		
	run();
}

void Game::run(void)
{
	m_Running = true;

	sf::Clock clock;

	while (m_Running)
	{
		sf::sleep(sf::milliseconds(10));

		sGUIMANAGER.update(clock.getElapsedTime());

		handleEvents();

		clock.restart();

		m_Window.setView(m_View);
		m_Window.clear(sf::Color(25, 25, 25, 255));

		m_Window.draw(sGUIMANAGER);

		m_Window.display();
	}
}

void Game::handleEvents(void)
{
	sf::Event event;

	while (m_Window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_Running = false;
		}
		else 
		{
			m_InputManager.handleEvent(event);
		}
	}
}
