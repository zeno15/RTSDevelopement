#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "../../ZenosGUI/ZenosGUI/ZenosGUIGlobalInclude.h"
#include "Map.h"

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

	bool											m_Running;

	Map												m_Map;

private:
    Game(void);
    ~Game(void);

	void run(void);

	void handleEvents(void);
};

#define sGame			Game::instance()
#define sFont			sGame.m_FontManager
#define sTexture		sGame.m_TextureManager
#define sInput			sGame.m_InputManager

#endif //~ INCLUDED_GAME_H