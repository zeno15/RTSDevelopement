#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "../../ZenosGUI/ZenosGUI/FontManager.h"
#include "../../ZenosGUI/ZenosGUI/GUIManager.h"
#include "../../ZenosGUI/ZenosGUI/InputManager.h"
#include "../../ZenosGUI/ZenosGUI/TextureManager.h"
#include "DebugManager.h"
#include "WorldObjectManager.h"


#include "World.h"

#include "PathfindingNode.h"

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

	std::vector<PathfindingNode *>					DEBUG_PathNodes;

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