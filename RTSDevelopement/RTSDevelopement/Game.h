#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H

#include <SFML/Graphics.hpp>

#include "FontManager.h"
#include "InputManager.h"
#include "GUIManager.h"

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
	GUIManager										m_GUIManager;

	bool											m_Running;

	bool											m_ButtonTest;
	float 											m_SliderTest;
	float											m_SliderTest2;

	void buttonActivated(void);
private:
    Game(void);
    ~Game(void);

	void run(void);

	void handleEvents(void);
};

#define sGame Game::instance()

#endif //~ INCLUDED_GAME_H