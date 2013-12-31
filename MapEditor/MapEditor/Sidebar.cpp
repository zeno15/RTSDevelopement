#include "Sidebar.h"

#include "Game.h"

Sidebar::Sidebar(void) :
	m_BackgroundQuads(sf::Quads, 4),
	m_SelectButtonActive(false)
{
}

Sidebar::~Sidebar(void)
{
}


void Sidebar::initialise(sf::FloatRect _bounds)
{
	m_BackgroundQuads[0] = sf::Vertex(sf::Vector2f(_bounds.left,
												   _bounds.top),
									  sf::Color(155, 155, 155, 255));
	m_BackgroundQuads[1] = sf::Vertex(sf::Vector2f(_bounds.left + _bounds.width,
												   _bounds.top),
									  sf::Color(155, 155, 155, 255));
	m_BackgroundQuads[2] = sf::Vertex(sf::Vector2f(_bounds.left + _bounds.width,
												   _bounds.top + _bounds.height),
									  sf::Color(155, 155, 155, 255));
	m_BackgroundQuads[3] = sf::Vertex(sf::Vector2f(_bounds.left,
												   _bounds.top + _bounds.height),
									  sf::Color(155, 155, 155, 255));

	GUIFrame *ToolButtons = new GUIFrame(); 

	GUIButtonTextured *selectButton = new GUIButtonTextured(sf::Vector2f(100.0f, 100.0f), 
															sf::Vector2f(50.0f, 50.0f), 
															&m_SelectButtonActive, 
															sGUITEX->getTexture(TextureManager::TextureID::TILESHEET), 
															sf::FloatRect(50.0f, 50.0f, 50.0f, 50.0f)); 

	ToolButtons->addObject(selectButton);

	sGUIMANAGER.addFrame(ToolButtons);
}

void Sidebar::update(sf::Time _delta)
{
	if (m_SelectButtonActive)
	{
		std::cout << "Woohoo!" << std::endl;
	}
}
void Sidebar::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.setView(_target.getDefaultView());

	_target.draw(m_BackgroundQuads,		_states);

	_target.setView(sGame.m_View);
}