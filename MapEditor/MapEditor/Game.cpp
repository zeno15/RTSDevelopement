#include "Game.h"

#include <ctime>
#include <cstdlib>

#include "NewMapInterface.h"

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

	m_CursorManager.initialise();

	m_InputManager.registerGUIManager(&sGUIMANAGER);

	sGUIMANAGER.linkWindow(&m_Window);
	sGUIMANAGER.linkFontManager(&m_FontManager);
	sGUIMANAGER.linkInputManager(&m_InputManager);
	sGUIMANAGER.linkTextureManager(&m_TextureManager);

	//NewMapInterface *newMap = new NewMapInterface(sf::Vector2f((float)(_screenSize.x), (float)(_screenSize.y)));

	//sGUIMANAGER.addFrame(newMap);

	//m_Map.create(sf::Vector2u(128, 128));

	GUIFrame *frame = new GUIFrame();

	std::vector<std::vector<std::string>> menuNames = std::vector<std::vector<std::string>>(3);

	menuNames.at(0) = std::vector<std::string>(3);
	menuNames.at(0).at(0) = "0-0";
	menuNames.at(0).at(1) = "0-1";
	menuNames.at(0).at(2) = "0-2";
	menuNames.at(1) = std::vector<std::string>(3);
	menuNames.at(1).at(0) = "1-0";
	menuNames.at(1).at(1) = "1-1";
	menuNames.at(1).at(2) = "1-2";
	menuNames.at(2) = std::vector<std::string>(3);
	menuNames.at(2).at(0) = "2-0";
	menuNames.at(2).at(1) = "2-1";
	menuNames.at(2).at(2) = "2-2";

	GUIDropDownMenu *menu = new GUIDropDownMenu(sf::Vector2f(100.0f, 100.0f), 84.0f, "Test menu", menuNames);

	frame->addObject(menu);

	sGUIMANAGER.addFrame(frame);
		
	run();
}

void Game::run(void)
{
	m_Running = true;

	sf::Clock clock;

	while (m_Running)
	{
		sf::sleep(sf::milliseconds(10));

		//m_Map.update(clock.getElapsedTime());
		sGUIMANAGER.update(clock.getElapsedTime());
		//m_CursorManager.update(clock.getElapsedTime());

		handleEvents();

		clock.restart();

		m_Window.setView(m_View);
		m_Window.clear(sf::Color(25, 25, 25, 255));

		//m_Window.draw(m_Map);

		m_Window.setView(m_Window.getDefaultView());
		m_Window.draw(sGUIMANAGER);

		//m_Window.setView(m_View);
		//m_Window.draw(m_CursorManager);

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
