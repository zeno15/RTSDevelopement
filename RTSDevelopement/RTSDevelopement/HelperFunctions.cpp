#include "HelperFunctions.h"

bool signChange2d(sf::Vector2f _dir1, sf::Vector2f _dir2)
{
	if ((_dir1.x > 0.0f && _dir2.x < 0.0f) || 
		(_dir1.x < 0.0f && _dir2.x > 0.0f) || 
		(_dir1.y > 0.0f && _dir2.y < 0.0f) ||
		(_dir1.y < 0.0f && _dir2.y > 0.0f)) return true;

	return false;
}