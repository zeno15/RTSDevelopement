#ifndef INCLUDED_GUIFRAME_H
#define INCLUDED_GUIFRAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "GUIObject.h"
#include "Receiver.h"

class GUIFrame : public sf::Drawable
{
public:
	GUIFrame(sf::FloatRect _bounds = sf::FloatRect());
	~GUIFrame(void);

	void addObject(GUIObject *_object);

	void update(sf::Time _delta);
	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

	bool toRemove(void);

	void toggleVisibility(void);

protected:
	std::vector<GUIObject *>						m_Objects;

	bool											m_ToRemove;
	bool											m_Display;
	bool											m_Update;

	unsigned int									m_ActiveObject;

	sf::VertexArray									m_VerticesBackground;
	sf::VertexArray									m_VerticesBorder;
};	

#endif //~ INCLUDED_GUIFRAME_H