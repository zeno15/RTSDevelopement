#include "Game.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

#include "GUIButton.h"
#include "GUISlider.h"
#include "GUIProgressBar.h"
#include "GUICheckbox.h"
#include "GUIRadioButtonGroup.h"
#include "GUITextBox.h"
#include "GUIDropDownBox.h"
#include "GUIMarkingMenu.h"
#include "GUIDropDownMenu.h"

#include "TestWorldObject.h"
#include "TestRandomWanderer.h"

Game::Game(void)
{
}


Game::~Game(void)
{
	m_FontManager.unloadAllFonts();
	m_TextureManager.unloadAllTextures();
	m_GUIManager.~GUIManager(); //~ Just so the pointer analysis is valid
	m_WorldObjectManager.~WorldObjectManager();
	m_World.~World();

	sDebug.analysePointers();
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

	m_DebugManager.initialise();

	m_World.setInterfaceSized(200.0f, 20.0f);
	m_World.load("Resources/Maps/map1.png");

	sInput.registerButton(sf::Mouse::Right);
		
	run();
}

void Game::run(void)
{
	m_Running = true;

	sf::Clock clock;
	while (m_Running)
	{
		//sf::sleep(sf::milliseconds(10));

		m_World.update(clock.getElapsedTime());
		sGUI.update(clock.getElapsedTime());
		sWorldObj.update(clock.getElapsedTime());
		sDebug.update(clock.getElapsedTime());

		if (!sInput.getButtonState(sf::Mouse::Right) && sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			/*sf::Vector2f offset(m_View.getCenter() - m_View.getSize() / 2.0f);
			TestRandomWanderer *newTest = new TestRandomWanderer(WorldObject::ObjectType::TEST, sf::Vector2f((float)(sf::Mouse::getPosition(m_Window).x), (float)(sf::Mouse::getPosition(m_Window).y)) + offset, sf::Vector2f(32.0f, 32.0f));
			mDebugNew(newTest);
			sWorldObj.addWorldObject(newTest);*/

			PathfindingNode *newPathNode = nullptr;

			sf::Vector2u mousePos = sf::Vector2u(((unsigned int)(sf::Mouse::getPosition(m_Window).x) / 32u) * 32u, ((unsigned int)(sf::Mouse::getPosition(m_Window).y) / 32u) * 32u);
			
			if (DEBUG_PathNodes.size() == 0)
			{
				newPathNode = new PathfindingNode(mousePos, mousePos, nullptr);
			}
			else
			{
				newPathNode = new PathfindingNode(mousePos, mousePos, DEBUG_PathNodes.back());
			}

			for (PathfindingNode *node : DEBUG_PathNodes)
			{
				node->changePathEnd(mousePos);
			}

			DEBUG_PathNodes.push_back(newPathNode);
		}

		handleEvents();

		clock.restart();

		m_Window.setView(m_View);
		m_Window.clear(sf::Color(25, 25, 25, 255));

		m_Window.draw(sWorld);
		m_Window.draw(sWorldObj);
		m_Window.draw(sGUI);
		m_Window.draw(sDebug);
		m_Window.setView(m_View);
		for (PathfindingNode *node : DEBUG_PathNodes)
		{
			m_Window.draw(*node);
		}

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
