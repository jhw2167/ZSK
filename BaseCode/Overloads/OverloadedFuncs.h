/*
	OverloadedFuncs.cpp file define operation overloads
*/

#pragma once
#include "../pch/stdafx.h"
#include "../Exceptions/Exceptions.h"


sf::Vector2f operator*(sf::Vector2f v1, int const& a);

sf::Vector2f operator/(const sf::Vector2f v1, const sf::Vector2f v2);

sf::Vector2f abs(sf::Vector2f v1);

sf::Vector2f convert(const sf::Vector2i& vec);

//Stream overloaders
std::ostream& operator<< (std::ostream &out, const sf::Vector2f v1);

std::ostream& operator<< (std::ostream &out, const sf::Vector2i v1);
