#pragma once

#include "../pch/stdafx.h"

/*
	Upstream file of global constants, colors for 
	the program to use
*/

namespace zsk {

	/* Non art related global constants */ 

	const static double pi = 3.141592628;
	extern enum FONT_CODES {ARIAL = 0, ARCDE};

	namespace art {

		/*	Art related global constants	*/
		
		//Const font variables
		extern sf::Font arcade;
		extern sf::Font arial;

		extern void loadFonts();


		//Const color variables
		extern sf::Color primColor;
		extern sf::Color secColor;

		//light and dark tertiary colors
		extern sf::Color lightTertCol;
		extern sf::Color darkTertCol;

		extern sf::Color winClearColor;

	}
}