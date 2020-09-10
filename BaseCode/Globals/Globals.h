#pragma once

#include "../pch/stdafx.h"

/*
	Upstream file of global constants, colors for 
	the program to use
*/

//Global Enum Defined in .h for gameState Handling
enum STATE { MAIN_MENU = 0, 
	LOBBY, 
	HOST_LOBBY, 
	JOIN_LOBBY,
	GAME, PAUSE, 
	SHOP, 
	QUIT};


namespace zsk {

	/* Non art related global constants */ 

	const static double pi = 3.141592628;
	enum FONT_CODE {ARIAL = 0, ARCDE};

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


	/*  Functions  */
	void print(const std::string& msg, int& counter, int tmp = 200);
}