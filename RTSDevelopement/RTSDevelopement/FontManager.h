#ifndef INCLUDED_FONTMANAGER_H
#define INCLUDED_FONTMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class FontManager
{
public:
	FontManager(void);
	~FontManager(void);

	enum FontID {OPENSANS_BOLD,
		         OPENSANS_BOLDITALIC,
				 OPENSANS_EXTRABOLD,
				 OPENSANS_EXTRABOLDITALIC,
				 OPENSANS_ITALIC,
				 OPENSANS_LIGHT,
				 OPENSANS_LIGHTITALIC,
				 OPENSANS_REGULAR,
				 OPENSANS_SEMIBOLD,
				 OPENSANS_SEMIBOLDITALIC,
				 NUMFONTS};

	void loadAllFonts(void);
	void unloadAllFonts(void);

	sf::Font *getFont(FontID _id);

private:
	std::vector<sf::Font *>					m_Fonts;
	std::vector<std::string>				m_Filepaths;

};

#endif //~ INCLUDED_FONTMANAGER_H