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
	struct vect {
		float a, b;

		vect(float a1 = 0.f, float b1 = 0.f) :
			a(a1), b(b1) {};
	};

	zsk::vect randomSpawn(const vect& range_x,
		const vect& range_y = vect(0.f, 1.f) );

	float distanceFrom(const sf::Vector2f& loc1,
		const sf::Vector2f& loc2);

	float magnitude(float x, float y); 
		
}