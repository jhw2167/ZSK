#pragma once

/*
	Menu objects such as buttons and text entry boxes
	will reside here for use in menus in game
*/

#include "../../BaseCode/pch/stdafx.h"
#include "../../BaseCode/Globals/Globals.h"

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
		//window pointer
		const sf::RenderWindow* win_ptr;

		//size and dewaults
		sf::Vector2f size;
		static sf::Vector2f defSize;

		//position of box
		sf::Vector2f pos;
		sf::RectangleShape shape;
		float outThickness;
		
		//text to display
		sf::Text text;
		int textSize;

		enum fontCode{ARIAL = 0, 
					  ARCDE};

		/*  Private Methods  */

		//For hidden resizing methods
		void calcDefaultSizes();
		void initText(const std::string& newString = "", 
			const short font = ARIAL);
		void initSizes();
		void initPositions(const sf::Vector2f& pos);
		void initColors(const sf::Color& prim = zsk::art::primColor,
			const sf::Color& sec = zsk::art::secColor,
			const sf::Color& txt = zsk::art::secColor);


		//For Button functionality and animation
		bool checkHovering();
		void animateOnHover();

	public:
		/*  Constructors  */

		//Default constructor - gives blank button
		Button(const sf::RenderWindow &window, const sf::Vector2f& pos);

		/*  Init Methods  */

		/*  Accessors  */
		std::string getString() const;
		bool isHovered() const;
		bool isClicked() const;

		//button color
		sf::Color getPrimColor() const;

		//outline color
		sf::Color getSecColor() const;
		sf::Color getTxtColor() const;


		/*  Modifiers  */
		void setString(const std::string& newString);
		void setSize(const float multiplier);

		void getPrimColor(const sf::Color& newPrim) ;
		void setSecColor(const sf::Color& newSec);
		void setTxtColor(const sf::Color& newTxtcolor);

		
		/*  Other Public Methods  */
		void update();


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


