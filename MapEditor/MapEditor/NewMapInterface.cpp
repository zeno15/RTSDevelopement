#include "NewMapInterface.h"

#include "GUIButton.h"
#include "GUITextBox.h"
#include "GUIRadioButtonGroup.h"

NewMapInterface::NewMapInterface(sf::Vector2f _screenSize) :
	GUIFrame(sf::FloatRect(_screenSize.x / 4.0f,
						   _screenSize.y / 4.0f,
						   _screenSize.x / 2.0f,
						   _screenSize.y / 2.0f)),
	m_Checking(false),
	m_WidthReceived(false),
	m_HeightReceived(false),
	m_Width(0),
	m_Height(0),
	m_DefaultTerrain(0)
{
	GUIButton *createButton = new GUIButton("Create map.", sf::Vector2f(_screenSize.x * 3.0f / 4.0f - 66.0f,
																		_screenSize.y * 3.0f / 4.0f - 20.0f));
	createButton->registerReceiver(this);

	GUITextBox *widthBox =  new GUITextBox(sf::Vector2f(_screenSize.x * 3.0f / 8.0f, _screenSize.y * 3.0f / 8.0f),
										   sf::Vector2f(80.0f,  40.0f),
										   GUITextBox::TextBoxType::NUMERICAL);
	m_WidthTextId = widthBox->registerReceiver(this);
	this->registerReceiver(widthBox);

	GUITextBox *heightBox = new GUITextBox(sf::Vector2f(_screenSize.x * 5.0f / 8.0f, _screenSize.y * 3.0f / 8.0f),
										   sf::Vector2f(80.0f,  40.0f),
										   GUITextBox::TextBoxType::NUMERICAL);
	m_HeightTextId = heightBox->registerReceiver(this);
	this->registerReceiver(heightBox);

	GUIRadioButtonGroup *group = new GUIRadioButtonGroup(sf::Vector2f(_screenSize.x * 5.0f / 16.0f, _screenSize.y / 2.0f),
														 100.0f, 
														 true);

	group->registerReceiver(this);
	group->addRadioButton("Grass");
	group->addRadioButton("Stone");
	group->addRadioButton("Water");
	group->addRadioButton("Dirt");

	m_Objects.push_back(createButton);
	m_Objects.push_back(widthBox);
	m_Objects.push_back(heightBox);
	m_Objects.push_back(group);

	std::cout << "New map created, objects size: " << m_Objects.size() << std::endl;
}


NewMapInterface::~NewMapInterface(void)
{
	notifyReceivers(MessageData::MessageType::DROPDOWN_UNACTIVE);

	std::cout << "New map deleted, objects size: " << m_Objects.size() << std::endl;
}


void NewMapInterface::update(sf::Time _delta)
{
	if (!m_Update) return;
	
	for (unsigned int i = 0; i < m_Objects.size(); i += 1)
	{
		m_Objects.at(i)->update(_delta);
		
		if (m_Objects.at(i)->remove())
		{
			delete m_Objects.at(i);
			m_Objects.erase(m_Objects.begin() + i);
			if (m_Objects.size() == 0) m_ToRemove = true;
		}
	}

	while (m_Messages.size() > 0)
	{
		if (m_Messages.front().s_MessageType == MessageData::MessageType::BUTTON_ACTIVATED)
		{
			m_Checking = true;
			notifyReceivers(MessageData::MessageType::TEXTBOX_REQUEST_TEXT);
		}
		else if (m_Messages.front().s_MessageType == MessageData::MessageType::TEXTBOX_DELIVER_TEXT)
		{
			if (m_Messages.front().s_Id == m_WidthTextId)
			{
				m_WidthReceived = true;
				m_Width = (unsigned int)(std::stoi(m_Messages.front().s_StringData));
			}
			else if (m_Messages.front().s_Id == m_HeightTextId)
			{
				m_HeightReceived = true;
				m_Height = (unsigned int)(std::stoi(m_Messages.front().s_StringData));
			}
		}
		else if (m_Messages.front().s_MessageType == MessageData::MessageType::RADIOBUTTON_CHANGE)
		{
			m_DefaultTerrain = (unsigned int)(m_Messages.front().s_FloatData);
		}

		m_Messages.erase(m_Messages.begin());
	}

	if (m_Checking && m_WidthReceived && m_HeightReceived)
	{
		m_WidthReceived = false;
		m_HeightReceived = false;
		m_ToRemove = checkInputs();
	}
}

void NewMapInterface::onReceiverRegistered(Receiver *_receiver)
{
	MessageData message = MessageData();
	message.s_MessageType = MessageData::MessageType::DROPDOWN_ACTIVE;

	_receiver->notify(message);
}

bool NewMapInterface::checkInputs(void)
{
	if (!(m_Width < 192u))
	{
		//~ Pop up message
		return false;
	}
	if (!(m_Height < 192u))
	{
		//~ Pop up message
		return false;
	}

	notifyReceivers(MessageData::MessageType::NEW_MAP_BOUNDS, (float)(m_DefaultTerrain), std::to_string(m_Width) + "x" + std::to_string(m_Height));
	return true;
}