#include "Game.h"

#include <iostream>

#include "GUIButton.h"
#include "GUISlider.h"
#include "GUIProgressBar.h"
#include "GUICheckbox.h"
#include "GUIRadioButtonGroup.h"
#include "GUITextBox.h"
#include "GUIDropDownBox.h"
#include "GUIMarkingMenu.h"
#include "GUIDropDownMenu.h"

Game::Game(void)
{
}


Game::~Game(void)
{
	m_FontManager.unloadAllFonts();
	m_GUIManager.~GUIManager(); //~ Just so the pointer analysis is valid

	sDebug.analysePointers();
}

void Game::initialise(sf::Vector2u _screenSize, std::string _windowName)
{
	m_ScreenSize = _screenSize;
	
	
	m_View.setSize  ((float)(m_ScreenSize.x),			(float)(m_ScreenSize.y));
	m_View.setCenter((float)(m_ScreenSize.x / 2.0f),	(float)(m_ScreenSize.y / 2.0f));

	m_Window.create(sf::VideoMode(_screenSize.x, _screenSize.y), _windowName);

	m_FontManager.loadAllFonts();

	GUIFrame *newFrame = new GUIFrame(sf::FloatRect());
	mDebugNew(newFrame)

	m_ButtonTest = false;
	GUIButton *newButton = new GUIButton("Mark's Button", &m_ButtonTest, sf::Vector2f(100.0f, 100.0f), sf::Vector2f());
	mDebugNew(newButton)

	m_SliderTest = 0.0f;
	GUISlider *newSlider = new GUISlider(true, sf::Vector2f(100.0f, 200.0f), 150.0f, &m_SliderTest2);
	mDebugNew(newSlider)

	m_SliderTest2 = 0.0f;
	GUISlider *newSlider2 = new GUISlider(true, sf::Vector2f(100.0f, 150.0f), 150.0f, &m_SliderTest);
	mDebugNew(newSlider2)

	GUIProgressBar *newProgress = new GUIProgressBar(true, sf::Vector2f(100.0f, 250.0f), sf::Vector2f(100.0f, 25.0f), &m_SliderTest, &m_SliderTest2);
	mDebugNew(newProgress)
	
	m_CheckboxTest = false;
	GUICheckbox *newCheckbox = new GUICheckbox(sf::Vector2f(100.0f, 50.0f), &m_CheckboxTest, "Hello!");
	mDebugNew(newCheckbox)

	GUIRadioButtonGroup *newRadioGroup = new GUIRadioButtonGroup(sf::Vector2f(200.0f, 50.0f), 24.0f);
	mDebugNew(newRadioGroup)

	newRadioGroup->addRadioButton("First");
	newRadioGroup->addRadioButton("Second");
	newRadioGroup->addRadioButton("Third");
	newRadioGroup->addRadioButton("Fourth");
	newRadioGroup->addRadioButton("Fifth");

	GUITextBox *newTextBox = new GUITextBox(sf::Vector2f(350.0f, 50.0f), sf::Vector2f(100.0f, 25.0f), true);
	mDebugNew(newTextBox)

	GUIDropDownBox *newDropDownBox = new GUIDropDownBox(sf::Vector2f(350.0f, 100.0f), sf::Vector2f(100.0f, 25.0f));
	mDebugNew(newDropDownBox)
	newDropDownBox->addOption("Option1");
	newDropDownBox->addOption("Option2");
	newDropDownBox->addOption("Option3");
	newDropDownBox->addOption("Option4");

	GUIMarkingMenu *newMarkingMenu = new GUIMarkingMenu();
	mDebugNew(newMarkingMenu)

	GUIDropDownMenu *newDropDownMenu = new GUIDropDownMenu("DROP DOWN", sf::Vector2f(350.0f, 250.0f), 100.0f);
	mDebugNew(newDropDownMenu)

	newFrame->addObject(newButton);
	newFrame->addObject(newSlider);
	newFrame->addObject(newSlider2);
	newFrame->addObject(newProgress);
	newFrame->addObject(newCheckbox);
	newFrame->addObject(newRadioGroup);
	newFrame->addObject(newTextBox);
	newFrame->addObject(newDropDownBox);
	newFrame->addObject(newMarkingMenu);
	newFrame->addObject(newDropDownMenu);

	m_GUIManager.addFrame(newFrame);
		
	run();
}

void Game::run(void)
{
	m_Running = true;

	sf::Clock clock;
	while (m_Running)
	{
		sf::sleep(sf::milliseconds(15));

		m_GUIManager.update(clock.getElapsedTime());

		if (m_ButtonTest)
		{
			buttonActivated();
		}
		
		handleEvents();

		clock.restart();

		m_Window.clear(sf::Color(25, 25, 25, 255));

		m_Window.draw(m_GUIManager);

		m_Window.display();
	}
}

void Game::handleEvents(void)
{
	sf::Event event;

	while (m_Window.pollEvent(event))
	{
		m_InputManager.handleEvent(event);
	}
}

void Game::buttonActivated(void)
{
	std::cout << "Button activated!" << std::endl;
}