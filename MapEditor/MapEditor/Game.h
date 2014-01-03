#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "../../ZenosGUI/ZenosGUI/ZenosGUIGlobalInclude.h"
#include "Map.h"
#include "CursorManager.h"

#define MOUSE_POSITION_WINDOW		(sf::Vector2f((float)(sf::Mouse::getPosition(sGame.m_Window).x), (float)(sf::Mouse::getPosition(sGame.m_Window).y)))
#define MOUSE_POSITION_VIEW			(sf::Vector2f((float)(sf::Mouse::getPosition(sGame.m_Window).x), (float)(sf::Mouse::getPosition(sGame.m_Window).y)) + sGame.m_View.getCenter() - sGame.m_View.getSize() / 2.0f)

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
	TextureManager									m_TextureManager;

	InputManager									m_InputManager;

	CursorManager									m_CursorManager;

	bool											m_Running;

	Map												m_Map;

	

private:
    Game(void);
    ~Game(void);

	void run(void);

	void handleEvents(void);
};

void functionToBePointered(void);

#define sGame			Game::instance()
#define sFont			sGame.m_FontManager
#define sTexture		sGame.m_TextureManager
#define sInput			sGame.m_InputManager
#define sCursor			sGame.m_CursorManager

#endif //~ INCLUDED_GAME_H