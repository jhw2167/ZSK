#pragma once

#include "../pch/stdafx.h"

/*
	functions.h supplies namespace level functions for the program to use 
	under the namespace ZSK, functions include:
		- randomloc(rangeX, rangeY)
		- distanceFrom(loc1, loc2)

*/

namespace zsk
{
	sf::Vector2f randomLoc(const sf::Vector2f& range_x,
		const sf::Vector2f& range_y)
	{
		float rand_x;
		float rand_y;

		return sf::Vector2f(rand_x, rand_y);
	}

	float distanceFrom(sf::Vector2f& loc1, sf::Vector2f& loc2)
	{

	}
}