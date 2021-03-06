#ifndef INCLUDED_HELPERFUNCTIONS_H
#define INCLUDED_HELPERFUNCTIONS_H

#define PI					3.14159265359f
#define TO_RADIANS			PI / 180.0f
#define TO_DEGREES			180.0f / PI

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>
#include <string>

template <typename T>
T clamp(T _x, T _min, T _max)
{
	return _x < _min ? _min : (_x > _max ? _max : _x);
}

template <typename T>
T distance2d(sf::Vector2<T> _point1, sf::Vector2<T> _point2)
{
	return sqrt((_point1.x - _point2.x) * (_point1.x - _point2.x) + (_point1.y - _point2.y) * (_point1.y - _point2.y));
}

bool signChange2d(sf::Vector2f _dir1, sf::Vector2f _dir2);

template <typename T>
void printvector2(sf::Vector2<T> _vector, std::string _description = "")
{
	std::cout << _description << " x: " << _vector.x << ", y: " << _vector.y << std::endl;
}

template <class T>
std::ostream & operator<<(std::ostream & stream, sf::Vector2<T> vec) {

	stream << "x : " << (int) vec.x;
	stream << " y : " << (int) vec.y;

	return stream;
}

#endif //~ INCLUDED_HELPERFUNCTIONS_H