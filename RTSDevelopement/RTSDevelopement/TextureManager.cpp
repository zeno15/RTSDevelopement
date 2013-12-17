#include "TextureManager.h"

#include "Game.h"

TextureManager::TextureManager(void) :
	m_Textures(TextureID::NUMTEXTURES, nullptr)
{
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
		mDebugNew(m_Textures.at(i))
		m_Textures.at(i)->loadFromFile(m_Filepaths.at(i));
	}
}
void TextureManager::unloadAllTextures(void)
{
	for (unsigned int i = 0; i < m_Textures.size(); i += 1)
	{
		if (m_Textures.at(i) == nullptr) continue;

		mDebugDelete(m_Textures.at(i))
		delete m_Textures.at(i);
		m_Textures.at(i) = nullptr;
	}
}

sf::Texture *TextureManager::getTexture(TextureID _id)
{
	return m_Textures.at(_id);
}