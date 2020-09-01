#pragma once

/*
	Menu objects such as buttons and text entry boxes
	will reside here for use in menus in game
*/

#include "../../BaseCode/pch/stdafx.h"
#include "../../BaseCode/Globals/Globals.h"
#include "../../BaseCode/Overloads/OverloadedFuncs.h"

namespace MenuObjects {
	
	enum fontCode {
		ARIAL = 0,
		ARCDE
	};

	/*  Menu Object Base Class - for buttons, text boxes and others  */

	class MenuObject{

	protected:
		//core quantities
		sf::RectangleShape box;
		sf::Text text;
		sf::Vector2f tightness;
		sf::Color primColor;

		sf::Vector2f boxSize;
		sf::Vector2f textDims;

		//Animation quantities
		sf::Color animateColor;
		sf::Vector2f animateScale;
		bool clickable;
		bool hovered;
		bool clicked;

		/*
			Buttons concists of a simple box and text with
			a tightness factor indicating how tighly the button
			grips the text
		*/


		//For hidden resizing methods
		void initText(const std::string& msg,
			const short font);
		void initColors(const sf::Color& prim = zsk::art::primColor,
			const sf::Color& sec = zsk::art::secColor,
			const sf::Color& txt = zsk::art::secColor);


		//For Button functionality and animation
		virtual void animateOnHover() = 0;
		virtual void resetSize() = 0;
		void waitForUnclick();

	public:
		/*  Constructors  */

		//Default constructor - Blank Button
		MenuObject();

		MenuObject(const sf::Vector2f& pos, const std::string& msg,
			const short fontCode = ARIAL, const int textSize = 20,
			const bool canBeClicked = true,
			const sf::Vector2f& tghtness = sf::Vector2f(1.1, 1.2));

		/*  Init Methods  */

		/*  Accessors  */
		std::string getString() const;
		bool isHovered(sf::RenderWindow& window) const;
		bool isClicked() const;
		bool isClickable() const;

		//button color
		sf::Color getPrimColor() const;

		//outline color
		sf::Color getSecColor() const;
		sf::Color getTxtColor() const;


		/*  Modifiers  */
		void setString(const std::string& newString);
		void setSize(const int textSize, const sf::Vector2f&
			tightness, const bool init = false);

		void setOutlineThickness(const int thickness);
		void setPosition(const sf::Vector2f& pos);

		void setPrimColor(const sf::Color& newPrim);
		void setSecColor(const sf::Color& newSec);
		void setTxtColor(const sf::Color& newTxtcolor);
		void setAnimateColor(const sf::Color& newCol);
		void setAnimateScaler(const sf::Vector2f & newScale);

		void setClickable(const bool canBeClicked);


		/*  Other Public Methods  */
		virtual void update(sf::RenderWindow& window) = 0;
		void bufferClickable();
		virtual void draw(sf::RenderWindow& window) = 0;

	};

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
	class Button : public MenuObject
	{
	private:
		
		/*
			Buttons concists of a simple box and text with
			a tightness factor indicating how tighly the button
			grips the text
		*/
		
		/*  Virtual Private Methods  */
		void animateOnHover();
		void resetSize();

	public:
		/*  Constructors  */

		//Default constructor - Blank Button
		Button();

		Button(const sf::Vector2f& pos, const std::string& msg,
			const short fontCode = ARIAL, const int textSize = 20, 
			const bool canBeClicked = true,
			const sf::Vector2f& tightness = sf::Vector2f(1.1, 1.1));


		/*  Virtual Public Methods  */
		void update(sf::RenderWindow& window);
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
	class Textbox : public MenuObject
	{
	private:
		sf::Text entry;
		short maxMsgSize;

		int interval;
		int counter;

		std::vector<sf::Event>* events;
		bool lockClick;
		//ensures textbox can only be clicked once when engaged

		bool rmDefTextOpts;
		//removes desault text options

		/*  Virtual Private Methods  */
		void animateOnHover();
		void resetSize();

		/*  Unique Private text Methods  */
		void checkTextInput(sf::RenderWindow& window);
		void animateCursor(std::string newMsg);
		void removeDefText();

	public:
		/*  Constructors  */

		//Default constructor - Textbox
		Textbox();

		Textbox(const sf::Vector2f& pos, const std::string& msg,
			const short fontCode = ARIAL, const int textSize = 20,
			const bool canBeClicked = true,
			const sf::Vector2f& tghtnss = sf::Vector2f(1.1, 1.1));

		/*  Unique Public methods */
		void setEventsPtr(std::vector<sf::Event>* evs);
		void setString(const std::string & newString);

		/*  Virtual Public Methods  */
		void update(sf::RenderWindow& window);
		void draw(sf::RenderWindow& window);

		~Textbox();
	};


}


