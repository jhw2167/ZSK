#pragma once

/*
	Menu objects such as buttons and text entry boxes
	will reside here for use in menus in game
*/

#include "../../BaseCode/pch/stdafx.h"

namespace MenuObjects {
	
	/*
		First class if interest is the "Button" class,
		a button knows:
		- its size, shape and position
		- the text it displays, as a string
		- the font its using
		- when it is hovered over, animation therefore
		- its secondary color to change to
		- if it has been pressed
	*/


	//BUTTON CLASS
	class Button
	{
	private:

	public:
		Button();
		~Button();
	};


	/*
		Second class of interest is the "Textbox" class,
		a Textbox knows:
		- its size, shape and position
		- the (default) text it displays, as a string
		- the font its using
		- when it is hovered over, animation therefore
		- its secondary color to change to
		- if it has been pressed
		- gives blinking cursor symbol
		- how to make text appear after user types it
	*/

	//TEXTBOX CLASS
	class Textbox
	{
	private:

	public:
		Textbox();
		~Textbox();
	};
}


