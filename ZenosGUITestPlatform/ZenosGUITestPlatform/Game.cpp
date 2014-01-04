#include "Game.h"

#include <ctime>
#include <cstdlib>


Game::Game(void)
{
}


Game::~Game(void)
{
	m_FontManager.unloadAllFonts();
	m_TextureManager.unloadAllTextures();
}

void Game::initialise(sf::Vector2u _screenSize, std::string _windowName)
{
	srand((unsigned int)time(nullptr));

	m_ScreenSize = _screenSize;
	
	m_View.setSize  ((float)(m_ScreenSize.x),			(float)(m_ScreenSize.y));
	m_View.setCenter((float)(m_ScreenSize.x / 2.0f),	(float)(m_ScreenSize.y / 2.0f));

	m_Window.create(sf::VideoMode(_screenSize.x, _screenSize.y), _windowName);

	m_FontManager.loadAllFonts();
	m_TextureManager.loadAllTextures();


	m_InputManager.registerGUIManager(&sGUIMANAGER);

	sGUIMANAGER.linkWindow(&m_Window);
	sGUIMANAGER.linkFontManager(&m_FontManager);
	sGUIMANAGER.linkInputManager(&m_InputManager);
	sGUIMANAGER.linkTextureManager(&m_TextureManager);

	GUIFrame *frame = new GUIFrame();

	GUICheckbox *check = new GUICheckbox(sf::Vector2f(25.0f, 25.0f), "<- Checkbox");
	check->registerReceiver(this);

	GUIButton *button = new GUIButton("Button", sf::Vector2f(50.0f, 50.0f));
	button->registerReceiver(this);

	GUIButton *textboxbutton = new GUIButton("Press to activate textbox", sf::Vector2f(150.0f, 300.0f));
	m_ActivateTextBoxID = textboxbutton->registerReceiver(this);

	GUITextBox *textbox = new GUITextBox(sf::Vector2f(150.0f, 250.0f), sf::Vector2f(234.0f, 24.0f), GUITextBox::TextBoxType::REGULAR);
	textbox->registerReceiver(this);
	this->registerReceiver(textbox);	

	GUIButtonTextured *buttonTex = new GUIButtonTextured(sf::Vector2f(50.0f, 100.0f), sf::Vector2f(50.0f, 25.0f), nullptr, sf::FloatRect());
	buttonTex->registerReceiver(this);	

	GUISlider *slider = new GUISlider(true, sf::Vector2f(50.0f, 150.0f), 80.0f);
	m_ProgressBarSliderID = slider->registerReceiver(this);

	GUISlider *slider2 = new GUISlider(true, sf::Vector2f(150.0f, 150.0f), 80.0f, 8);
	slider2->registerReceiver(this);

	GUIProgressBar *progress = new GUIProgressBar(true, sf::Vector2f(50.0f, 200.0f), sf::Vector2f(100.0f, 40.0f));
	this->registerReceiver(progress);

	GUIRadioButtonGroup *group = new GUIRadioButtonGroup(sf::Vector2f(25.0f, 350.0f), 25.0f);
	group->registerReceiver(this);
	group->addRadioButton("First!");
	group->addRadioButton("Second!");
	group->addRadioButton("Third!");

	GUIDropDownBox *dropbox = new GUIDropDownBox(sf::Vector2f(250.0f, 25.0f), sf::Vector2f(100.0f, 24.0f));
	dropbox->registerReceiver(this);
	dropbox->addOption("First");
	dropbox->addOption("Second");
	dropbox->addOption("Third");
	dropbox->addOption("Fourth");
	dropbox->addOption("Fifth");

	std::vector<std::vector<std::string>> menuNames = std::vector<std::vector<std::string>>(4);

	menuNames.at(0) = std::vector<std::string>(3);
	menuNames.at(0).at(0) = "Hello";
	menuNames.at(0).at(1) = "I'm";
	menuNames.at(0).at(2) = "Zeno!";
	menuNames.at(1) = std::vector<std::string>(2);
	menuNames.at(1).at(0) = "Oi!";
	menuNames.at(1).at(1) = "Boo!";
	menuNames.at(2) = std::vector<std::string>(3);
	menuNames.at(2).at(0) = "Sausages";
	menuNames.at(2).at(1) = "Bacon";
	menuNames.at(2).at(2) = "and HAM!";
	menuNames.at(3) = std::vector<std::string>(1);
	menuNames.at(3).at(0) = "Exit-ish";

	GUIDropDownMenu *dropmenu = new GUIDropDownMenu(sf::Vector2f(250.0f, 75.0f), 130.0f, "DropDownMenu", menuNames);
	dropmenu->registerReceiver(this);

	frame->addObject(check);
	frame->addObject(button);
	frame->addObject(textboxbutton);
	frame->addObject(textbox);
	frame->addObject(buttonTex);
	frame->addObject(slider);
	frame->addObject(slider2);
	frame->addObject(progress);
	frame->addObject(group);
	frame->addObject(dropbox);
	frame->addObject(dropmenu);

	sGUIMANAGER.addFrame(frame);

	run();
}

void Game::run(void)
{
	m_Running = true;

	sf::Clock clock;

	while (m_Running)
	{
		sf::sleep(sf::milliseconds(10));

		sGUIMANAGER.update(clock.getElapsedTime());

		//~ Update start
		while (m_Messages.size() > 0)
		{
			if (m_Messages.front().s_MessageType == MessageData::MessageType::BUTTON_ACTIVATED)
			{
				if (m_Messages.front().s_Id == m_ActivateTextBoxID)
				{
					notifyReceivers(MessageData::MessageType::TEXTBOX_REQUEST_TEXT);
				}
				else
				{
					std::cout << "Button activated" << std::endl;
				}
			}
			else if (m_Messages.front().s_MessageType == MessageData::MessageType::CHECKBOX_ACTIVATED)
			{
				std::cout << "Checkbox activated" << std::endl;
			}
			else if (m_Messages.front().s_MessageType == MessageData::MessageType::CHECKBOX_DEACTIVATED)
			{
				std::cout << "Checkbox deactivated" << std::endl;
			}
			else if (m_Messages.front().s_MessageType == MessageData::MessageType::SLIDER_UPDATED)
			{
				std::cout << "Slider updated: " << m_Messages.front().s_FloatData << "%" << std::endl;
				if (m_Messages.front().s_Id == m_ProgressBarSliderID)
				{
					notifyReceivers(MessageData::MessageType::PROGRESSBAR_COMPLETE_PERC, m_Messages.front().s_FloatData);
				}
			}
			else if (m_Messages.front().s_MessageType == MessageData::MessageType::TEXTBOX_DELIVER_TEXT)
			{
				std::cout << "Textbox says: " << m_Messages.front().s_StringData << std::endl;
			}
			else if (m_Messages.front().s_MessageType == MessageData::MessageType::RADIOBUTTON_CHANGE)
			{
				std::cout << "Radio button now active is: " << m_Messages.front().s_StringData << std::endl;
			}
			else if (m_Messages.front().s_MessageType == MessageData::MessageType::DROPDOWN_ACTIVE)
			{
				std::cout << "Dropdown gui item active, stop updating everything else" << std::endl;
			}
			else if (m_Messages.front().s_MessageType == MessageData::MessageType::DROPDOWN_UNACTIVE)
			{
				std::cout << "Dropdown gui item unactive, start updating everything else again" << std::endl;
			}
			else if (m_Messages.front().s_MessageType == MessageData::MessageType::DROPDOWN_BOX_SELECT)
			{
				std::cout << "Dropdown box choice is: " << m_Messages.front().s_StringData << std::endl;
			}
			else if (m_Messages.front().s_MessageType == MessageData::MessageType::DROPDOWN_MENU_SELECT)
			{
				std::cout << "Dropdown menu choice is: " << m_Messages.front().s_StringData << std::endl;
			}

			m_Messages.erase(m_Messages.begin());
		}
		//~ Update end

		handleEvents();

		clock.restart();

		m_Window.setView(m_View);
		m_Window.clear(sf::Color(25, 25, 25, 255));

		m_Window.setView(m_Window.getDefaultView());
		m_Window.draw(sGUIMANAGER);


		m_Window.display();
	}
}

void Game::handleEvents(void)
{
	sf::Event event;

	while (m_Window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_Running = false;
		}
		else 
		{
			m_InputManager.handleEvent(event);
		}
	}
}

