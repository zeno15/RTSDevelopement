#include "GUIManager.h"

#include "GUITextBox.h"
#include "Game.h"

GUIManager::GUIManager(void)
{
}

GUIManager::~GUIManager(void)
{
}


void GUIManager::addFrame(GUIFrame *_frame)
{
	m_Frames.push_back(_frame);
}

void GUIManager::update(sf::Time _delta)
{
	for (unsigned int i = 0; i < m_Frames.size(); i += 1)
	{
		m_Frames.at(i)->update(_delta);
		
		if (m_Frames.at(i)->toRemove())
		{
			delete m_Frames.at(i);
			m_Frames.erase(m_Frames.begin() + i);
		}
	}
}
	
void GUIManager::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	for (unsigned int i = 0; i < m_Frames.size(); i += 1)
	{
		_target.draw(*m_Frames.at(i),		_states);
	}
}

void GUIManager::sendTextToTextBoxes(char _character)
{
	for (unsigned int i = 0; i < m_TextBoxes.size(); i += 1)
	{
		if (m_TextBoxes.at(i)->active())
		{
			m_TextBoxes.at(i)->appendTextInput(_character);
			break;		//~ Because you can only have one active text box at a time
		}
	}
}

void GUIManager::addGUITextBoxToReceiveText(GUITextBox *_textBox)
{
	m_TextBoxes.push_back(_textBox);
	sGame.m_InputManager.registerTextInput();
}
void GUIManager::removeGUITextBoxToReceiveText(GUITextBox *_textBox)
{
	for (unsigned int i = 0; i < m_TextBoxes.size(); i += 1)
	{
		if (_textBox == m_TextBoxes.at(i))
		{
			m_TextBoxes.erase(m_TextBoxes.begin() + i);
			sGame.m_InputManager.unregisterTextInput();
		}
	}
}