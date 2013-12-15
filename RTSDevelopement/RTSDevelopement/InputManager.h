#ifndef INCLUDED_INPUTMANAGER_H
#define INCLUDED_INPUTMANAGER_H

#include <SFML/Window.hpp>
#include <vector>
#include <map>

class InputManager
{
public:
	InputManager(void);
	~InputManager(void);

	void registerKey(sf::Keyboard::Key _key);
	void unRegisterKey(sf::Keyboard::Key _key);

	void registerButton(sf::Mouse::Button _button);
	void unregisterButton(sf::Mouse::Button _button);

	bool getKeyState(sf::Keyboard::Key _key);
	bool getButtonState(sf::Mouse::Button _button);
	
	void handleEvent(sf::Event const &_event);
	
private:
	std::map<sf::Keyboard::Key, bool>					m_KeyDictionary;
	std::vector<bool>									m_KeyStates;
	std::vector<unsigned int>							m_KeyRegisterRequests;

	std::map<sf::Mouse::Button, bool>					m_ButtonDictionary;
	std::vector<bool>									m_ButtonStates;
	std::vector<unsigned int>							m_ButtonRegisterRequests;
};

#endif //~ INCLUDED_INPUTMANAGER_H