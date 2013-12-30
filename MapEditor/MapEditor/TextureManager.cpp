#include "TextureManager.h"

#include "Game.h"

TextureManager::TextureManager(void) :
	m_Textures(TextureID::NUMTEXTURES, nullptr)
{
	std::cout << "Maximum texture dimensions: " << sf::Texture::getMaximumSize() << std::endl;

	m_Filepaths.push_back("../../Resources/Textures/Tilesheet.png");
}

TextureManager::~TextureManager(void)
{
}



void TextureManager::loadAllTextures(void)
{
	for (unsigned int i = 0; i < m_Textures.size(); i += 1)
	{
		if (m_Textures.at(i) != nullptr) continue;

		m_Textures.at(i) = new sf::Texture();
		m_Textures.at(i)->loadFromFile(m_Filepaths.at(i));
	}
}
void TextureManager::unloadAllTextures(void)
{
	for (unsigned int i = 0; i < m_Textures.size(); i += 1)
	{
		if (m_Textures.at(i) == nullptr) continue;

		delete m_Textures.at(i);
		m_Textures.at(i) = nullptr;
	}
}

sf::Texture *TextureManager::getTexture(TextureID _id)
{
	return m_Textures.at(_id);
}