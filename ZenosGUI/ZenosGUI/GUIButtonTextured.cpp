#include "GUIButtonTextured.h"

#include "GUIManager.h"

#define GUI_DEFAULT_BUTTON_SIZE			sf::Vector2f(40.0f, 40.0f) 
#define GUI_BUTTON_OUTLINE				1.0f
#define GUI_TEXT_BOX_DISPLACEMENT		3.0f

GUIButtonTextured::GUIButtonTextured(sf::Vector2f _position, sf::Vector2f _size, bool *_toActivate, sf::Texture *_texture, sf::FloatRect _textureBounds) :
	m_Vertices(sf::Quads, 12),
	m_CurrentState(colourState::NORMAL),
	m_ToActivate(_toActivate),
	m_Unactivate(false),
	m_Texture(_texture)
{
	sf::FloatRect bounds = sf::FloatRect(_position.x - _size.x / 2.0f, _position.y - _size.y / 2.0f, _size.x, _size.y);

	sf::Color outline = sf::Color(165, 165, 165, 255);
	sf::Color inner   = sf::Color(91, 91, 91, 255);

	m_Vertices[0] = sf::Vertex(sf::Vector2f(bounds.left,					bounds.top),					outline);
	m_Vertices[1] = sf::Vertex(sf::Vector2f(bounds.left + bounds.width,		bounds.top),					outline);
	m_Vertices[2] = sf::Vertex(sf::Vector2f(bounds.left + bounds.width,		bounds.top + bounds.height),	outline);
	m_Vertices[3] = sf::Vertex(sf::Vector2f(bounds.left,					bounds.top + bounds.height),	outline);

	m_Vertices[4] = sf::Vertex(sf::Vector2f(bounds.left + GUI_BUTTON_OUTLINE,					bounds.top + GUI_BUTTON_OUTLINE),					inner);
	m_Vertices[5] = sf::Vertex(sf::Vector2f(bounds.left + bounds.width - GUI_BUTTON_OUTLINE,	bounds.top + GUI_BUTTON_OUTLINE),					inner);
	m_Vertices[6] = sf::Vertex(sf::Vector2f(bounds.left + bounds.width - GUI_BUTTON_OUTLINE,	bounds.top + bounds.height - GUI_BUTTON_OUTLINE),	inner);
	m_Vertices[7] = sf::Vertex(sf::Vector2f(bounds.left + GUI_BUTTON_OUTLINE,					bounds.top + bounds.height - GUI_BUTTON_OUTLINE),	inner);

	m_Vertices[ 8] = sf::Vertex(m_Vertices[4].position, sf::Color::White, sf::Vector2f(_textureBounds.left,							_textureBounds.top));
	m_Vertices[ 9] = sf::Vertex(m_Vertices[5].position, sf::Color::White, sf::Vector2f(_textureBounds.left + _textureBounds.width,	_textureBounds.top));
	m_Vertices[10] = sf::Vertex(m_Vertices[6].position, sf::Color::White, sf::Vector2f(_textureBounds.left + _textureBounds.width,	_textureBounds.top + _textureBounds.height));
	m_Vertices[11] = sf::Vertex(m_Vertices[7].position, sf::Color::White, sf::Vector2f(_textureBounds.left,							_textureBounds.top + _textureBounds.height));

	sGUIINPUT->registerButton(sf::Mouse::Left);
}

GUIButtonTextured::~GUIButtonTextured(void)
{
	sGUIINPUT->unregisterButton(sf::Mouse::Left);
}


void GUIButtonTextured::update(sf::Time _delta)
{
	if (!m_Update) return;
	if (*m_ToActivate && m_Unactivate)
	{
		*m_ToActivate = false;
		m_Unactivate = false;
	}

	if (m_Vertices.getBounds().contains(sf::Vector2f((float)(sf::Mouse::getPosition(*sGUIWINDOW).x), (float)(sf::Mouse::getPosition(*sGUIWINDOW).y))))
	{
		
		if (!sGUIINPUT->getButtonState(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			changeColourState(colourState::CLICK);
		}
		else if (sGUIINPUT->getButtonState(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			changeColourState(colourState::HOVER);
			*m_ToActivate = true;
			m_Unactivate = true;
		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			changeColourState(colourState::HOVER);
		}
	}
	else
	{
		changeColourState(colourState::NORMAL);
	}
}
	
void GUIButtonTextured::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	if (!m_Display) return;
	_states.texture = m_Texture;

	_target.draw(m_Vertices,			_states);
}

void GUIButtonTextured::changeColourState(colourState _state){
	if (_state == m_CurrentState) return;

	m_CurrentState = _state;

	switch (m_CurrentState)
	{
	case (colourState::HOVER):
		setHoverColours();
		return;
	case (colourState::CLICK):
		setPressedColours();
		return;
	case (colourState::NORMAL):
	default:
		setDefaultColours();
	};

}

void  GUIButtonTextured::setDefaultColours(void)
{
	m_Vertices[0].color = sf::Color(155, 155, 155, 255);
	m_Vertices[1].color = sf::Color(155, 155, 155, 255);
	m_Vertices[2].color = sf::Color(155, 155, 155, 255);
	m_Vertices[3].color = sf::Color(155, 155, 155, 255);

	m_Vertices[4].color = sf::Color(100, 100, 100, 255);
	m_Vertices[5].color = sf::Color(100, 100, 100, 255);
	m_Vertices[6].color = sf::Color(100, 100, 100, 255);
	m_Vertices[7].color = sf::Color(100, 100, 100, 255);
}
void  GUIButtonTextured::setHoverColours(void)
{
	m_Vertices[0].color = sf::Color(94, 155, 255, 255);
	m_Vertices[1].color = sf::Color(94, 155, 255, 255);
	m_Vertices[2].color = sf::Color(94, 155, 255, 255);
	m_Vertices[3].color = sf::Color(94, 155, 255, 255);

	m_Vertices[4].color = sf::Color(100, 100, 100, 255);
	m_Vertices[5].color = sf::Color(100, 100, 100, 255);
	m_Vertices[6].color = sf::Color(100, 100, 100, 255);
	m_Vertices[7].color = sf::Color(100, 100, 100, 255);
}
void  GUIButtonTextured::setPressedColours(void)
{
	m_Vertices[0].color = sf::Color(94, 155, 255, 255);
	m_Vertices[1].color = sf::Color(94, 155, 255, 255);
	m_Vertices[2].color = sf::Color(94, 155, 255, 255);
	m_Vertices[3].color = sf::Color(94, 155, 255, 255);

	m_Vertices[4].color = sf::Color(65, 65, 65, 255);
	m_Vertices[5].color = sf::Color(65, 65, 65, 255);
	m_Vertices[6].color = sf::Color(65, 65, 65, 255);
	m_Vertices[7].color = sf::Color(65, 65, 65, 255);
}