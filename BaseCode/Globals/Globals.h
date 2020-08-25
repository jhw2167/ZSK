#pragma once

#include "../pch/stdafx.h"

/*
	Upstream file of global constants, colors for 
	the program to use
*/

namespace zsk {

	/* Non art related global constants */ 

	const static double pi = 3.141592628;

	namespace art {

		//Art related global constants
		//Const variables
		extern sf::Color primColor;
		extern sf::Color secColor;

		extern sf::Color winClearColor;

	}
}