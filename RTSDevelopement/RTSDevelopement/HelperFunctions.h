#ifndef INCLUDED_HELPERFUNCTIONS_H
#define INCLUDED_HELPERFUNCTIONS_H

template <typename T>
T clamp(T _x, T _min, T _max)
{
	return _x < _min ? _min : (_x > _max ? _max : _x);
}

#endif //~ INCLUDED_HELPERFUNCTIONS_H