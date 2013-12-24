#include "Game.h"

#include <iostream>

#include "GUIButton.h"
#include "GUISlider.h"
#include "GUIProgressBar.h"
#include "GUICheckbox.h"
#include "GUIRadioButtonGroup.h"
#include "GUITextBox.h"
#include "GUIDropDownBox.h"
#include "GUIMarkingMenu.h"
#include "GUIDropDownMenu.h"

Game::Game(void)
{
}


Game::~Game(void)
{
	m_FontManager.unloadAllFonts();
	m_TextureManager.unloadAllTextures();
	m_GUIManager.~GUIManager(); //~ Just so the pointer analysis is valid

	sDebug.analysePointers();
}

void Game::initialise(sf::Vector2u _screenSize, std::string _windowName)
{
	m_ScreenSize = _screenSize;
	
	
	m_View.setSize  ((float)(m_ScreenSize.x),			(float)(m_ScreenSize.y));
	m_View.setCenter((float)(m_ScreenSize.x / 2.0f),	(float)(m_ScreenSize.y / 2.0f));

	m_Window.create(sf::VideoMode(_screenSize.x, _screenSize.y), _windowName);

	m_FontManager.loadAllFonts();
	m_TextureManager.loadAllTextures();

	m_World.setInterfaceSized(200.0f, 20.0f);
	m_World.load("Resources/Maps/map1.png");
		
	run();
}

void Game::run(void)
{
	m_Running = true;

	sf::Clock clock;
	while (m_Running)
	{
		sf::sleep(sf::milliseconds(10));

		m_World.update(clock.getElapsedTime());
		sGUI.update(clock.getElapsedTime());
		sWorldObj.update(clock.getElapsedTime());

		handleEvents();

		clock.restart();

		m_Window.setView(m_View);
		m_Window.clear(sf::Color(25, 25, 25, 255));

		m_Window.draw(m_World);
		m_Window.draw(sWorldObj);
		m_Window.draw(sGUI);

		m_Window.display();
	}
}

void Game::handleEvents(void)
{
	sf::Event event;

	while (m_Window.pollEvent(event))
	{
		sInput.handleEvent(event);
	}
}
