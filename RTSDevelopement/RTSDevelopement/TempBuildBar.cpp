#include "TempBuildBar.h"

#include "Game.h"

#include "WorldBuildingFootprint.h"

#include <iostream>

TempBuildBar::TempBuildBar(sf::FloatRect _bounds) :
	m_Bounds(_bounds)
{
	GUIFrame * frame = new GUIFrame();

	GUIButton * createFootprintButton = new GUIButton("Test place", sf::Vector2f(m_Bounds.left + m_Bounds.width / 2.0f, m_Bounds.top + m_Bounds.height / 2.0f));
	createFootprintButton->registerReceiver(this);

	frame->addObject(createFootprintButton);

	sGUI.addFrame(frame);
}

TempBuildBar::~TempBuildBar(void)
{
}


void TempBuildBar::update(sf::Time _delta)
{
	while (m_Messages.size() > 0)
	{
		if (m_Messages.front().s_MessageType == MessageData::MessageType::BUTTON_ACTIVATED)
		{
			std::cout << "Build bar activated" << std::endl;
			
			WorldBuildingFootprint *footprint = new WorldBuildingFootprint(sf::Vector2f(96.0f, 96.0f), Tile::Type::INFANTRY);

			footprint->registerReceiver(this);
			this->registerReceiver(footprint);

			sWorldObj.addWorldObject(footprint);
		}

		m_Messages.erase(m_Messages.begin());
	}
}
void TempBuildBar::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
}