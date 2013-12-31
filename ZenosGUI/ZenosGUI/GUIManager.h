#ifndef INCLUDED_GUIMANAGER_H
#define INCLUDED_GUIMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "GUIFrame.h"
#include "FontManager.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "../../RTSDevelopement/RTSDevelopement/HelperFunctions.h"

class GUITextBox;

class GUIManager : public sf::Drawable
{
public:
	static GUIManager& instance()
	{
		static GUIManager guiManager;
		return guiManager;
	}

	void addFrame(GUIFrame *_frame);

	void update(sf::Time _delta);
	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

	void sendTextToTextBoxes(char _character);

	void addGUITextBoxToReceiveText(GUITextBox *_textBox);
	void removeGUITextBoxToReceiveText(GUITextBox *_textBox);

	void linkFontManager(FontManager *_fontManager);
	FontManager *getFontManager(void);

	void linkTextureManager(TextureManager *_textureManager);
	TextureManager *getTextureManager(void);

	void linkInputManager(InputManager *_inputManager);
	InputManager *getInputManager(void);

	void linkWindow(sf::RenderWindow *_window);
	sf::RenderWindow *getWindow(void);

private:
	GUIManager(void);
	~GUIManager(void);

private:
	std::vector<GUIFrame *>										m_Frames;
	std::vector<GUITextBox *>									m_TextBoxes;

	FontManager *												m_FontManager;
	TextureManager *											m_TextureManager;
	InputManager *												m_InputManager;
	sf::RenderWindow *											m_Window;
};

#define sGUIMANAGER GUIManager::instance()
#define sGUIFONTS	GUIManager::instance().getFontManager()
#define sGUITEX		GUIManager::instance().getTextureManager()
#define sGUIINPUT	GUIManager::instance().getInputManager()
#define sGUIWINDOW	GUIManager::instance().getWindow()

#endif //~ INCLUDED_GUIMANAGER_H