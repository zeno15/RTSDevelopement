#ifndef INCLUDED_WORLDOBJECTHEALTH_H
#define INCLUDED_WORLDOBJECTHEALTH_H

#include <SFML/Graphics.hpp>

class WorldObjectHealth
{
public:
	WorldObjectHealth(sf::Vector2f _position, sf::Vector2f _size, int _maxHP, float _startPerc = 1.0f);
	~WorldObjectHealth(void);


	bool damage(int _amount); //~ Can be negative (i.e. healing), returns true if unit is killed

	void updateHealthPosition(sf::Vector2f _position);

	bool select(void);
	bool deselect(void);
	void toggleSelect(void);

private:
	void updateHealthBar(void);

protected:
	int										m_CurrentHP;
	int										m_MaxHP;

	sf::Vector2f							m_Size;

	bool									m_Selected;

	sf::VertexArray							m_SelectedCorners;
	sf::VertexArray							m_HealthBar;
};

#endif //~ INCLUDED_WORLDOBJECTHEALTH_H