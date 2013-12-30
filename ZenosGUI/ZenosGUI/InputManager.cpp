#include "InputManager.h"

#include "GUIManager.h"

#include <iostream>

InputManager::InputManager(void) :
	m_KeyStates(sf::Keyboard::KeyCount, false),
	m_KeyRegisterRequests(sf::Keyboard::KeyCount, 0u),
	m_ButtonStates(sf::Mouse::ButtonCount, false),
	m_ButtonRegisterRequests(sf::Mouse::ButtonCount, 0u),
	m_TextInputRegisterRequests(0u)
{
}

InputManager::~InputManager(void)
{
}


void InputManager::registerKey(sf::Keyboard::Key _key)
{
	//~ Increase registered key watch count
	m_KeyRegisterRequests.at(_key) += 1;


	if (m_KeyDictionary.find(_key) == m_KeyDictionary.end())
	{
		//~ Key is not present, add
		m_KeyDictionary.insert(std::pair<sf::Keyboard::Key, bool>(_key, true));
	}
}
void InputManager::unRegisterKey(sf::Keyboard::Key _key)
{
	if (m_KeyDictionary.find(_key) == m_KeyDictionary.end())
	{
		//~ Key wasn't being inspected
		return;
	}

	m_KeyRegisterRequests.at(_key) -= 1;

	if (m_KeyRegisterRequests.at(_key) > 0)
	{
		//~ Key is still being inspected
		return;
	}

	//~ Key is no longer being inspected, remove it from dictionary
	m_KeyDictionary.erase(_key);
}
void InputManager::registerButton(sf::Mouse::Button _button)
{
	//~ Increase registered button watch count
	m_ButtonRegisterRequests.at(_button) += 1;


	if (m_ButtonDictionary.find(_button) == m_ButtonDictionary.end())
	{
		//~ Button is not present, add
		m_ButtonDictionary.insert(std::pair<sf::Mouse::Button, bool>(_button, true));
	}
}
void InputManager::unregisterButton(sf::Mouse::Button _button)
{
	if (m_ButtonDictionary.find(_button) == m_ButtonDictionary.end())
	{
		//~ Button wasn't being inspected
		return;
	}

	m_ButtonRegisterRequests.at(_button) -= 1;

	if (m_ButtonRegisterRequests.at(_button) > 0)
	{
		//~ Button is still being inspected
		return;
	}

	//~ Button is no longer being inspected, remove it from dictionary
	m_ButtonDictionary.erase(_button);
}

bool InputManager::getKeyState(sf::Keyboard::Key _key)
{
	//~ This assumes you have registered the key you are asking for
	return m_KeyStates.at(_key);
}
bool InputManager::getButtonState(sf::Mouse::Button _button)
{
	return m_ButtonStates.at(_button);
}

void InputManager::registerGUIManager(GUIManager *_guiManager)
{
	m_GUIManager = _guiManager;
}
void InputManager::registerTextInput(void)
{
	m_TextInputRegisterRequests += 1;
	m_TextInputState = true;
}
void InputManager::unregisterTextInput(void)
{
	m_TextInputRegisterRequests -= 1;
	if (m_TextInputRegisterRequests <= 0)
	{
		m_TextInputRegisterRequests = 0;
		m_TextInputState = false;
	}
}

void InputManager::handleEvent(sf::Event const &_event)
{
	if (_event.type == sf::Event::KeyPressed)
	{
		if (m_KeyDictionary.find(_event.key.code) != m_KeyDictionary.end())
		{
			m_KeyStates.at(_event.key.code) = true;
		}
	}
	if (_event.type == sf::Event::KeyReleased)
	{
		if (m_KeyDictionary.find(_event.key.code) != m_KeyDictionary.end())
		{
			m_KeyStates.at(_event.key.code) = false;
		}
	}

	if (_event.type == sf::Event::MouseButtonPressed)
	{
		if (m_ButtonDictionary.find(_event.mouseButton.button) != m_ButtonDictionary.end())
		{
			m_ButtonStates.at(_event.mouseButton.button) = true;
		}
	}
	if (_event.type == sf::Event::MouseButtonReleased)
	{
		if (m_ButtonDictionary.find(_event.mouseButton.button) != m_ButtonDictionary.end())
		{
			m_ButtonStates.at(_event.mouseButton.button) = false;
		}
	}

	if (m_TextInputState && _event.type == sf::Event::TextEntered)
	{
		if (_event.text.unicode < 128)
		{
			m_GUIManager->sendTextToTextBoxes(static_cast<char>(_event.text.unicode));
		}
	}
}