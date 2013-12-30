#include "FontManager.h"

#include "Game.h"

FontManager::FontManager(void) :
	m_Fonts(FontID::NUMFONTS, nullptr)
{
	m_Filepaths.push_back("../../Resources/Fonts/OpenSans-Bold.ttf");
	m_Filepaths.push_back("../../Resources/Fonts/OpenSans-BoldItalic.ttf");
	m_Filepaths.push_back("../../Resources/Fonts/OpenSans-ExtraBold.ttf");
	m_Filepaths.push_back("../../Resources/Fonts/OpenSans-ExtraBoldItalic.ttf");
	m_Filepaths.push_back("../../Resources/Fonts/OpenSans-Italic.ttf");
	m_Filepaths.push_back("../../Resources/Fonts/OpenSans-Light.ttf");
	m_Filepaths.push_back("../../Resources/Fonts/OpenSans-LightItalic.ttf");
	m_Filepaths.push_back("../../Resources/Fonts/OpenSans-Regular.ttf");
	m_Filepaths.push_back("../../Resources/Fonts/OpenSans-Semibold.ttf");
	m_Filepaths.push_back("../../Resources/Fonts/OpenSans-SemiboldItalic.ttf");
}

FontManager::~FontManager(void)
{
	unloadAllFonts();
	m_Filepaths.clear();
}


void FontManager::loadAllFonts(void)
{
	for (unsigned int i = 0; i < m_Fonts.size(); i += 1)
	{
		if (m_Fonts.at(i) != nullptr) continue;

		m_Fonts.at(i) = new sf::Font();
		m_Fonts.at(i)->loadFromFile(m_Filepaths.at(i));
	}
}
void FontManager::unloadAllFonts(void)
{
	for (unsigned int i = 0; i < m_Fonts.size(); i += 1)
	{
		if (m_Fonts.at(i) == nullptr) continue;

		delete m_Fonts.at(i);
		m_Fonts.at(i) = nullptr;
	}
}

sf::Font *FontManager::getFont(FontID _id)
{
	return m_Fonts.at(_id);
}