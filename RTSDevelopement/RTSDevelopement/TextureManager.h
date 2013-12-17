#ifndef INCLUDED_TEXTUREMANAGER_H
#define INCLUDED_TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>

class TextureManager
{
public:
	TextureManager(void);
	~TextureManager(void);

	enum TextureID {
				 NUMTEXTURES};

	void loadAllTextures(void);
	void unloadAllTextures(void);

	sf::Texture *getTexture(TextureID _id);

private:
	std::vector<sf::Texture *>				m_Textures;
	std::vector<std::string>				m_Filepaths;
};

#endif //~ INCLUDED_TEXTUREMANAGER_H