#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "DebugManager.h"
#include "WorldObjectManager.h"
#include "../../../ZenosGUI/ZenosGUI/ZenosGUIGlobalInclude.h"

#include "World.h"
#include "Interface.h"


#define MOUSE_POSITION_WINDOW		sf::Vector2f((float)(sf::Mouse::getPosition(sGame.m_Window).x), (float)(sf::Mouse::getPosition(sGame.m_Window).y))
#define MOUSE_POSITION_VIEW			(MOUSE_POSITION_WINDOW + sGame.m_View.getCenter() - sGame.m_View.getSize() / 2.0f)
#define MOUSE_TILE_POSITION_VIEW	sf::Vector2f((float)((unsigned int)(MOUSE_POSITION_VIEW.x / TILESIZE_f) * TILESIZE_f),(float)((unsigned int)(MOUSE_POSITION_VIEW.y / TILESIZE_f) * TILESIZE_f))


class Game
{
public:
	static Game& instance()
	{
		static Game game;
		return game;
	}

	void initialise(sf::Vector2u _screenSize, std::string _windowName);

public:
	sf::Vector2u									m_ScreenSize;

	sf::RenderWindow								m_Window;
	sf::View										m_View;

	FontManager										m_FontManager;
	InputManager									m_InputManager;
	GUIManager *									m_GUIManager;
	DebugManager									m_DebugManager;
	WorldObjectManager								m_WorldObjectManager;
	TextureManager									m_TextureManager;

	World											m_World;
	Interface *										m_Interface;
		
	bool											m_Running;

private:
    Game(void);
    ~Game(void);

	void run(void);

	void handleEvents(void);
};

#define sGame			Game::instance()
#define sDebug			sGame.m_DebugManager
#define sFont			sGame.m_FontManager
#define sTexture		sGame.m_TextureManager
#define sGUI			GUIManager::instance()
#define sInput			sGame.m_InputManager
#define sWorldObj		sGame.m_WorldObjectManager
#define sWorld			sGame.m_World

#endif //~ INCLUDED_GAME_H