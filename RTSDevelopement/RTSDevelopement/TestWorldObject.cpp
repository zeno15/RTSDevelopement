#include "TestWorldObject.h"




TestWorldObject::TestWorldObject(ObjectType _type, sf::Vector2f _position, sf::Vector2f _size) :
	WorldObject(_type, _position, _size),
	m_Rect(_size)
{
	m_Rect.setOrigin(_size.x / 2.0f, _size.y / 2.0f);
	m_Rect.setPosition(_position);
	m_Rect.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 255));
}

TestWorldObject::~TestWorldObject(void)
{
}


void TestWorldObject::update(sf::Time _delta)
{
}
void TestWorldObject::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.draw(m_Rect,			_states);
}