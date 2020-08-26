/*
	OverloadedFuncs.cpp file includes .h file for implementation 
*/

#include "OverloadedFuncs.h";

/*	OVERLOADED OPERATORS	*/



sf::Vector2f operator*(sf::Vector2f v1, int const& a)
{
	sf::Vector2f ret;
	ret.x = v1.x * a;
	ret.y = v1.y * a;

	return ret;
}


sf::Vector2f operator /(const sf::Vector2f v1, const sf::Vector2f v2)
{
	float x = v1.x / v2.x;
	float y = v1.y / v2.y;

	return sf::Vector2f(x, y);
}

sf::Vector2f abs(sf::Vector2f v1) {
	float x = abs(v1.x);
	float y = abs(v1.y);

	return sf::Vector2f(x, y);
}

sf::Vector2f convert(const sf::Vector2i & vec) {
	return sf::Vector2f(vec.x, vec.y);
}


std::ostream& operator<< (std::ostream &out, const sf::Vector2f v1)
{
	out << "Vector x: " << v1.x << std::endl;
	out << "Vector y: " << v1.y << std::endl;
	out << std::endl;

	return out;
}

std::ostream& operator<< (std::ostream &out, const sf::Vector2i v1)
{
	out << "Vector x: " << v1.x << std::endl;
	out << "Vector y: " << v1.y << std::endl;
	out << std::endl;

	return out;
}
