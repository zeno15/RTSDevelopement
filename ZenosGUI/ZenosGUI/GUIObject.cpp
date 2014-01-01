#include "GUIObject.h"


GUIObject::GUIObject(void) :
	m_Display(true),
	m_Update(true),
	m_ToRemove(false)
{
}

GUIObject::~GUIObject(void)
{
}


bool GUIObject::toDisplay(void)
{
	return m_Display;
}
bool GUIObject::remove(void)
{
	return m_ToRemove;
}