#include "NewMapInterface.h"

#include "Game.h"

#define NEWMAP_MAX_WIDTH		512
#define NEWMAP_MAX_HEIGHT		512

NewMapInterface::NewMapInterface(sf::Vector2f _screenSize) :
	GUIFrame(sf::FloatRect(_screenSize.x / 4.0f, _screenSize.y / 4.0f, _screenSize.x / 2.0f, _screenSize.y / 2.0f))
{
	sf::FloatRect bounds(_screenSize.x / 4.0f, _screenSize.y / 4.0f, _screenSize.x / 2.0f, _screenSize.y / 2.0f);

	GUIButton *confirmButton = new GUIButton("Create Map", &m_OnConfirm, sf::Vector2f(bounds.left + bounds.width * 7.0f / 8.0f,
																					  bounds.top + bounds.height * 7.0f / 8.0f));

	GUITextBox *mapWidthText  = new GUITextBox(sf::Vector2f(bounds.left + bounds.width * 1.0f / 5.0f, bounds.top + bounds.height * 1.0f / 5.0f), sf::Vector2f(80.0f, 30.0f), GUITextBox::TextBoxType::NUMERICAL);
	mapWidthText->setLabel("Width", GUITextBox::LabelPosition::BELOW);
	m_WidthIndex = 1u;

	GUITextBox *mapHeightText = new GUITextBox(sf::Vector2f(bounds.left + bounds.width * 4.0f / 5.0f, bounds.top + bounds.height * 1.0f / 5.0f), sf::Vector2f(80.0f, 30.0f), GUITextBox::TextBoxType::NUMERICAL);
	mapHeightText->setLabel("Height", GUITextBox::LabelPosition::BELOW);
	m_HeightIndex = 2u;

	GUIDropDownBox *defaultTerrain = new GUIDropDownBox(sf::Vector2f(bounds.left + bounds.width * 2.5f / 5.0f, bounds.top + bounds.height * 3.0f / 5.0f), sf::Vector2f(80.0f, 24.0f));
	defaultTerrain->addOption("Grass");
	defaultTerrain->addOption("Stone");
	defaultTerrain->addOption("Water");


	addObject(confirmButton);
	addObject(mapWidthText);
	addObject(mapHeightText);
	addObject(defaultTerrain);

	sInput.registerButton(sf::Mouse::Left);
}


NewMapInterface::~NewMapInterface(void)
{
	sInput.unregisterButton(sf::Mouse::Left);
}

void NewMapInterface::checkValidInputs(void)
{
	GUITextBox *width  = (GUITextBox *)m_Objects.at(m_WidthIndex);
	GUITextBox *height = (GUITextBox *)m_Objects.at(m_HeightIndex);

	if (std::stoi(width->getString()) <= NEWMAP_MAX_WIDTH &&
		std::stoi(height->getString()) <= NEWMAP_MAX_HEIGHT)
	{
		std::cout << "Map is valid! at (W, H) - (" << std::stoi(width->getString()) << ", " << std::stoi(height->getString()) << ")" << std::endl;
	}

}