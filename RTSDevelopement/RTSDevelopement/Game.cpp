#include "Game.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

#include "HelperFunctions.h"

#include "WorldBuildingMilitaryTest.h"
#include "WorldBuildingFootprint.h"
#include "WorldUnitTriangleTest.h"

Game::Game(void)
{
}


Game::~Game(void)
{
	m_FontManager.unloadAllFonts();
	m_TextureManager.unloadAllTextures();
	
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
	//m_Window.setPosition(sf::Vector2i(500, 200));

	m_FontManager.loadAllFonts();
	m_TextureManager.loadAllTextures();

	m_DebugManager.initialise();

	m_World.setInterfaceSized(200.0f, 20.0f);
	m_World.load("../../Resources/Maps/Quadrant.RTSDMAP");

	sInput.registerButton(sf::Mouse::Right);

	//sWorldObj.addWorldObject(new WorldBuildingFootprint(sf::Vector2f(128.0f, 128.0f), Tile::Type::INFANTRY));
	sWorldObj.addWorldObject(new WorldUnitTriangleTest(sf::Vector2f(100.0f, 100.0f)));
		
	run();
}

void Game::run(void)
{
	m_Running = true;

	int state = 0;

	sf::Vector2f start;
	sf::Vector2f end;

	sf::Clock clock;
	while (m_Running)
	{
		sWorld.update(clock.getElapsedTime());
		sGUI.update(clock.getElapsedTime());
		sWorldObj.update(clock.getElapsedTime());
		sDebug.update(clock.getElapsedTime());

		

		if (!sInput.getButtonState(sf::Mouse::Right) && sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			WorldBuildingMilitaryTest *test = new WorldBuildingMilitaryTest(MOUSE_TILE_POSITION_VIEW);

			sWorldObj.addWorldObject(test);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			sWorld.m_PathfindingGrid.changeOverlay(Tile::Type::INFANTRY);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			sWorld.m_PathfindingGrid.changeOverlay(Tile::Type::LIGHT_VEHICLE);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			sWorld.m_PathfindingGrid.changeOverlay(Tile::Type::HEAVY_VEHICLE);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			sWorld.m_PathfindingGrid.changeOverlay(Tile::Type::NAVAL);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		{
			sWorld.m_PathfindingGrid.changeOverlay(Tile::Type::AIR);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
		{
			sWorld.m_PathfindingGrid.changeOverlay(Tile::Type::NUM_TYPES);
		}

		handleEvents();

		clock.restart();

		m_Window.setView(m_View);
		m_Window.clear(sf::Color(25, 25, 25, 255));

		m_Window.draw(sWorld);
		m_Window.draw(sWorldObj);
		m_Window.draw(sGUI);
		m_Window.draw(sDebug);

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

		sInput.handleEvent(event);
	}
}
