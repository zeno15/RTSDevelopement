#include "CursorManager.h"

#include "Game.h"

CursorManager::CursorManager(void) :
	m_DrawCursor(false)
{
	m_TextureRects.push_back(sf::IntRect(0,
										 0,
										 0,
										 0));
	m_TextureRects.push_back(sf::IntRect(0,
										 256,
										 32,
										 32));
	m_TextureRects.push_back(sf::IntRect(64,
										 256,
										 32,
										 32));
	m_TextureRects.push_back(sf::IntRect(32,
										 256,
										 32,
										 32));
	m_TextureRects.push_back(sf::IntRect(96,
										 256,
										 32,
										 32));
}

CursorManager::~CursorManager(void)
{
}


void CursorManager::initialise(void)
{
	m_Cursor = sf::Sprite(*sTexture.getTexture(TextureManager::TextureID::TILESHEET), sf::IntRect(0, 0, 32, 32));
	m_Cursor.setOrigin(m_Cursor.getGlobalBounds().width / 2.0f, m_Cursor.getGlobalBounds().height / 2.0f);
}

void CursorManager::changeCursor(CursorType _cursorType)
{
	if (_cursorType == CursorType::DEFAULT)
	{
		sGUIWINDOW->setMouseCursorVisible(true);
		m_DrawCursor = false;
	}
	else
	{
		sGUIWINDOW->setMouseCursorVisible(false);
		m_Cursor.setTextureRect(m_TextureRects.at(_cursorType));
		m_DrawCursor = true;
	}
}

void CursorManager::update(sf::Time _delta)
{
	m_Cursor.setPosition((float)(sf::Mouse::getPosition(*sGUIWINDOW).x), (float)(sf::Mouse::getPosition(*sGUIWINDOW).y));
}
void CursorManager::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.setView(_target.getDefaultView());

	if (m_DrawCursor) 
	{
		_target.draw(m_Cursor,			_states);
	}

	_target.setView(sGame.m_View);
}