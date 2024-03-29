#pragma once

#include "../../../BaseCode/pch/stdafx.h"
#include "../../../BaseCode/Overloads/OverloadedFuncs.h"
#include "../../../BaseCode/Globals/Globals.h"

/*
	functions.h supplies namespace level functions for the program to use 
	under the namespace ZSK, functions include:
		- randomloc(rangeX, rangeY)
		- distanceFrom(loc1, loc2)

*/

namespace zsk
{

	/*  Mathy Functions ZSK  */

	struct vect {
		float a, b;

		vect(float a1 = 0.f, float b1 = 0.f) :
			a(a1), b(b1) {};

		vect(int a1 = 0, int b1 = 0) :
			a(static_cast<float>(a1)), 
			b(static_cast<float>(b1)) {};
	};

	zsk::vect randomSpawn(const vect& range_x,
		const vect& range_y = vect(0.f, 1.f) );

	double distanceFrom(const sf::Vector2f& loc1,
		const sf::Vector2f& loc2);

	double magnitude(float x, float y); 

	//double comes with higher precision and makes superior temp variables
	double radsToDegs(double rads);
	
	//double comes with higher precision and makes superior temp variables
	double lawCosINV(double s1, double s2, double s3);

	/*  Artistic Functions and constants for ZSK  */

	namespace art 
	{
			/*  Art Variables  */

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