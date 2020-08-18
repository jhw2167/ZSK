#pragma once

#include "../../../BaseCode/pch/stdafx.h"
#include "../../../BaseCode/Overloads/OverloadedFuncs.h"

/*
	functions.h supplies namespace level functions for the program to use 
	under the namespace ZSK, functions include:
		- randomloc(rangeX, rangeY)
		- distanceFrom(loc1, loc2)

*/

namespace zsk
{

	/*  Mathy Functions and constants for ZSK  */

	const static double pi = 3.141592628;

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

	double radsToDegs(double rads);
		
	double lawCosINV(double s1, double s2, double s3);

	/*  Artistic Functions and constants for ZSK  */

	namespace art 
	{
			/*  Art Variables  */

		//Const variables
		extern sf::Color primColor;
		extern sf::Color secColor;

		extern sf::Color winClearColor;

		//non const variales
		extern std::vector<sf::Color> playerColors;


			/*  Art Functions  */
		sf::Image& changePixels(sf::Image& img, 
			const sf::Color& cFrom, const sf::Color& cTo, const int slack);

		sf::Image & changePixelRange(sf::Image & img,
			const sf::Color & cFrom, const sf::Color & cTo);

		int newCodeFromDiff(int minC, int maxC, int pixC);
	}

}