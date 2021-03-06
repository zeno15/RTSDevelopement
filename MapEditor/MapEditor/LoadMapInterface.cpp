#include "LoadMapInterface.h"

#include <fstream>

#include "../../../ZenosGUI/ZenosGUI/ZenosGUIGlobalInclude.h"


LoadMapInterface::LoadMapInterface(sf::Vector2f _screenSize) :
	GUIFrame(sf::FloatRect(_screenSize.x / 4.0f,
						   _screenSize.y / 4.0f,
						   _screenSize.x / 2.0f,
						   _screenSize.y / 2.0f))
{
	GUIButton *loadButton = new GUIButton("Load",
										  sf::Vector2f(_screenSize.x * 3.0f / 4.0f - 32.0f, _screenSize.y * 3.0f / 4.0f - 24.0f),
										  sf::Vector2f(60.0f, 24.0f));
	loadButton->registerReceiver(this);

	GUITextBox *filenameBox = new GUITextBox(sf::Vector2f(_screenSize.x / 2.0f, _screenSize.y / 2.0f),
											 sf::Vector2f(_screenSize.x / 4.0f, 24.0f),
											 GUITextBox::TextBoxType::REGULAR,
											 false);
	filenameBox->setLabel("Enter filename", GUITextBox::LabelPosition::BELOW);
	filenameBox->registerReceiver(this);
	this->registerReceiver(filenameBox);


	addObject(loadButton);
	addObject(filenameBox);
}

LoadMapInterface::~LoadMapInterface(void)
{
	notifyReceivers(MessageData::MessageType::DROPDOWN_UNACTIVE);
}



void LoadMapInterface::update(sf::Time _delta)
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
			notifyReceivers(MessageData::MessageType::TEXTBOX_REQUEST_TEXT);
		}
		else if (m_Messages.front().s_MessageType == MessageData::MessageType::TEXTBOX_DELIVER_TEXT)
		{
			if (checkValidity("../../Resources/Maps/" + m_Messages.front().s_StringData + ".RTSDMAP"))
			{
				notifyReceivers(MessageData::MessageType::LOAD_MAP_DATA, 0.0f, "../../Resources/Maps/" + m_Messages.front().s_StringData + ".RTSDMAP");
				m_ToRemove = true;
			}
		}

		m_Messages.erase(m_Messages.begin());
	}
}

void LoadMapInterface::onReceiverRegistered(Receiver *_receiver)
{
	MessageData message = MessageData();
	message.s_MessageType = MessageData::MessageType::DROPDOWN_ACTIVE;

	_receiver->notify(message);
}

bool LoadMapInterface::checkValidity(std::string _filename)
{
	std::ifstream input(_filename);

	if (input.is_open())
	{
		std::cout << "File exists!" << std::endl;
		input.close();
		return true;
	}
	else
	{
		std::cout << "Filename: " << _filename << " doesn't exist!" << std::endl;
		return false;
	}
}