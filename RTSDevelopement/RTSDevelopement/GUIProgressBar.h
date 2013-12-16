#ifndef INCLUDED_GUIPROGRESSBAR_H
#define INCLUDED_GUIPROGRESSBAR_H

#include "GUIObject.h"

class GUIProgressBar : public GUIObject
{
public:
	GUIProgressBar(bool _horizontal, sf::Vector2f _position, sf::Vector2f _size, float *_completedPercentage, float *_underwayPercentage = nullptr);
	~GUIProgressBar(void);

	virtual void update(sf::Time _delta);
	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

private:
	void resizeProgressBar(void);

private:
	sf::VertexArray								m_Vertices;

	float *										m_CompletedPercentage;
	float *										m_UnderwayPercentage;

	sf::Vector2f								m_Size;
};

#endif //~ INCLUDED_GUIPROGRESSBAR_H