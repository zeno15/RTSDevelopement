#ifndef INCLUDED_MESSAGEDATA_H
#define INCLUDED_MESSAGEDATA_H

#include <string>

struct MessageData
{
	enum MessageType {BUTTON_ACTIVATED,
					  CHECKBOX_ACTIVATED,
					  CHECKBOX_DEACTIVATED,
					  SLIDER_UPDATED,
					  PROGRESSBAR_COMPLETE_PERC,
					  PROGRESSBAR_UNDERWAY_PERC,
					  TEXTBOX_REQUEST_TEXT,
					  TEXTBOX_DELIVER_TEXT,
					  RADIOBUTTON_CHANGE,
					  DROPDOWN_ACTIVE,
					  DROPDOWN_UNACTIVE,
					  DROPDOWN_BOX_SELECT,
					  DROPDOWN_MENU_SELECT,
					  NEW_MAP_BOUNDS,
					  SAVE_MAP_DATA,
					  LOAD_MAP_DATA,
					  NUM_TYPES};

	unsigned int	s_Id;
	
	MessageType		s_MessageType;

	float			s_FloatData;

	std::string		s_StringData;
};

#endif //~ INCLUDED_MESSAGEDATA_H