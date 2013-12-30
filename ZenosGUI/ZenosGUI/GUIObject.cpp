#include "GUIObject.h"


GUIObject::GUIObject(void) :
	m_Display(true),
	m_Update(true)
{
}

GUIObject::~GUIObject(void)
{
}


bool GUIObject::toDisplay(void)
{
	return m_Display;
}