#pragma once

/*
	Menu objects such as buttons and text entry boxes
	will reside here for use in menus in game
*/

#include "../../BaseCode/pch/stdafx.h"
#include "../../BaseCode/Globals/Globals.h"
#include "../../BaseCode/Overloads/OverloadedFuncs.h"

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
	
		//core quantities
		sf::RectangleShape box;
		sf::Text text;
		sf::Vector2f tightness;
		sf::Color primColor;

		//Animation quantities
		sf::Color animateColor;
		bool hovered;
		bool clicked;
	
		/*
			Buttons concists of a simple box and text with
			a tightness factor indicating how tighly the button
			grips the text
		*/

		enum fontCode{ARIAL = 0, 
					  ARCDE};

		/*  Private Methods  */

		//For hidden resizing methods
		void initText(const std::string& msg, 
			const short font);
		void initColors(const sf::Color& prim = zsk::art::primColor,
			const sf::Color& sec = zsk::art::secColor,
			const sf::Color& txt = zsk::art::secColor);


		//For Button functionality and animation
		void animateOnHover();
		void resetSize();

	public:
		/*  Constructors  */

		//Default constructor - Blank Button
		Button();

		Button(const sf::Vector2f& pos, const std::string& msg,
			const short fontCode = ARIAL, const int textSize = 20, 
			const sf::Vector2f& tightness = sf::Vector2f(1.1, 1.1));

		/*  Init Methods  */

		/*  Accessors  */
		std::string getString() const;
		bool isHovered(const sf::RenderWindow& window) const;
		bool isClicked() const;

		//button color
		sf::Color getPrimColor() const;

		//outline color
		sf::Color getSecColor() const;
		sf::Color getTxtColor() const;


		/*  Modifiers  */
		void setString(const std::string& newString);
		void setSize(const int textSize, const sf::Vector2f&
			tightness);

		void setOutlineThickness(const int thickness);
		void setPosition(const sf::Vector2f& pos);

		void setPrimColor(const sf::Color& newPrim);
		void setSecColor(const sf::Color& newSec);
		void setTxtColor(const sf::Color& newTxtcolor);
		void setAnimateColor(const sf::Color& newCol);

		
		/*  Other Public Methods  */
		void update(const sf::RenderWindow& window);
		void draw(sf::RenderWindow& window);


		/*  Destructor  */
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


