#ifndef INCLUDED_TEMPBUILDBAR_H
#define INCLUDED_TEMPBUILDBAR_H

#include <SFML/Graphics.hpp>

#include "../../../ZenosGUI/ZenosGUI/ZenosGUIGlobalInclude.h"

class TempBuildBar : public sf::Drawable, public Receiver, public Publisher
{
public:
	TempBuildBar(sf::FloatRect _bounds);
	~TempBuildBar(void);

	void update(sf::Time _delta);
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

private:
	sf::FloatRect								m_Bounds;
};

#endif //~ INCLUDED_TEMPBUILDBAR_H