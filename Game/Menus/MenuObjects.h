#pragma once

/*
	Menu objects such as buttons and text entry boxes
	will reside here for use in menus in game
*/

#include "../../BaseCode/pch/stdafx.h"
#include "../../BaseCode/Globals/Globals.h"
#include "../../BaseCode/Overloads/OverloadedFuncs.h"

namespace MenuObjects {
	
	/*  Menu Object Base Class - for buttons, text boxes and others  */

	//For general alignment
	 enum ALIGN {
		LEFT = -1,
		CNTR = 0, RGHT = 1
	};

	class MenuObject{

	protected:
		//State quanities
		STATE currState;
		STATE nextState;

		//core quantities
		sf::RectangleShape box;
		sf::Text text;
		sf::Vector2f tightness;
		sf::Color primColor;
		sf::Color secColor;

		sf::Vector2f boxSize;
		sf::Vector2f textDims;
		ALIGN txtAlign;
		const static float adj;
		//text-box adjustment = 10.f

		//Animation quantities
		sf::Color animateColor;
		sf::Color animateColor2;
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
			const zsk::FONT_CODE font);
		void initColors(const sf::Color& prim = zsk::art::primColor,
			const sf::Color& sec = zsk::art::secColor,
			const sf::Color& txt = zsk::art::secColor);


		//For Button functionality and animation
		//virtual void animateOnHover();
		//virtual void resetSize();
		void waitForUnclick();

	public:
		/*  Constructors  */

		//Default constructor - Blank Button
		MenuObject();

		MenuObject(const STATE currentState, const sf::Vector2f& pos, const std::string& msg,
			const zsk::FONT_CODE fontCode = zsk::ARIAL, const int textSize = 20,
			const bool canBeClicked = true, const STATE newStateOnClick = MAIN_MENU,
			const sf::Vector2f& tghtness = sf::Vector2f(1.1, 1.1));

		MenuObject(const STATE currentState, const sf::Vector2f& pos,
			const sf::Vector2f& boxSize, const bool canBeClicked,
			const STATE newStateOnClick);


		//Copy Constructor
		MenuObject(const MenuObject& rhs);

		//End Constructors

		/*  Init Methods  */

		/*  Accessors  */
		virtual char getType() const = 0;
		std::string getString() const;
		int getTextSize() const;

		bool isHovered(sf::RenderWindow& window) const;
		bool isClicked() const;
		bool isClickable() const;

		sf::Vector2f getPosition() const;
		sf::Vector2f getBoxSize() const;

		//button color
		sf::Color getPrimColor() const;
		sf::Color getAnimateColor() const;

		//outline color
		sf::Color getSecColor() const;
		sf::Color getAnimateColor2() const;
		sf::Color getTxtColor() const;
		float getOutlineThickness() const;


		/*  Modifiers  */
		void setString(const std::string& newString);
		void setSize(const int textSize, const sf::Vector2f&
			tightness, const bool init = false);
		void setPosition(const sf::Vector2f& pos);
		void setBoxOrigin(const sf::Vector2f& org);
		void setBoxSize(const sf::Vector2f& size);
		void updateCurrState(const STATE curr);
		void updateNextState(const STATE next);

		//Set Text Facets
		void adjTextToBox(const sf::Vector2f& adj);
		void setOutlineThickness(const int thickness);
		void setTextStyle(const sf::Text::Style& style);
		void setTextSpacing(const float spc = 1);
		void setFont(const zsk::FONT_CODE font);
		void alignText(const ALIGN);
		
		//set Color Facets
		void setPrimColor(const sf::Color& newPrim);
		void setSecColor(const sf::Color& newSec);
		void setTxtColor(const sf::Color& newTxtcolor);

		void setAnimateColor(const sf::Color& newCol);
		void setAnimateColor2(const sf::Color& newCol);
		void setAnimateScaler(const sf::Vector2f & newScale);

		void setClickable(const bool canBeClicked);


		/*  Other Public Methods  */
		virtual STATE update(sf::RenderWindow& window) = 0;
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

		Button(STATE currentState, const sf::Vector2f& pos, const std::string& msg,
			const zsk::FONT_CODE fontCode = zsk::ARIAL, const int textSize = 20,
			const bool canBeClicked = true, STATE newStateOnClick = MAIN_MENU,
			const sf::Vector2f& tightness = sf::Vector2f(1.1, 1.1));

		//For use in tuples
		Button(const STATE currentState, const sf::Vector2f& pos,
			const sf::Vector2f& boxSize, const bool canBeClicked,
			const STATE newStateOnClick);


		/*  Virtual Public Methods  */
		char getType() const;
		STATE update(sf::RenderWindow& window);
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
		short maxMsgSize;
		bool forceUpperLetters;

		int interval;
		int counter;

		std::vector<sf::Event>* events;
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

		Textbox(STATE currentState, const sf::Vector2f& pos, const std::string& msg,
			const zsk::FONT_CODE fontCode = zsk::ARIAL, const int textSize = 20,
			const bool canBeClicked = true, STATE newStateOnClick = MAIN_MENU,
			const sf::Vector2f& tghtnss = sf::Vector2f(1.1, 1.1));

		//For use in tuples
		Textbox(const STATE currentState, const sf::Vector2f & pos,
			const sf::Vector2f & boxSize, const bool canBeClicked,
			const STATE newStateOnClick);

		/*  Unique Public methods */
		void setEventsPtr(std::vector<sf::Event>* evs);
		void setString(const std::string & newString);
		void setSize(const int textSize, const sf::Vector2f&
			tghtness, const bool init);
		void fitTextToBox(const sf::Vector2f& tightness,
			const ALIGN aln = CNTR);

		//Setters
		void setMaxMsgSize(short newSize);
		void forceUpperCase(bool force);

		//Accessors



		/*  Virtual Public Methods  */
		char getType() const;
		STATE update(sf::RenderWindow& window);
		void draw(sf::RenderWindow& window);

		~Textbox();
	};





	/*
		Third Class of interest is "tuple" class which
		will be a combination of n number of text boxes
		& buttons all kept together, a tuple knows

		- total length and percentage length of all objects
		- position of midpoint of the object
		- total standard height of the tuple
		- how to return a vector pointing to all 
		the menu objects inside the tuple	
	*/

	class Tuple :
		public MenuObject {

	private:

		/* Core entities */
		std::vector<MenuObject*> internals;
		std::vector<float> percLengths;
		std::vector<char> objTypes;


		/*  Private Methods  */
		void addObjs(const std::vector<char>& objs);

	public:
		Tuple(const STATE currentState, const sf::Vector2f& pos,
			const std::vector<char>& objs, std::vector<float>&
			percLengths, const sf::Vector2f& boxSize,
			const bool canBeClicked, const STATE newStateOnClick);

		//Copy Constructor - DELETED, use std::move(TupleObj)
		Tuple(Tuple&& rhs);

			/*  Public Methods  */

		/*  Unique Public Methods */
		void setOutlineThickness(float thickness);

		//Accessors
		std::vector<MenuObject*>* getObjs();
		char getType() const;

		
		//Virtual Functions
		STATE update(sf::RenderWindow& window);
		void updateCurrState(const STATE curr);
		void updateNextState(const STATE next);

		void draw(sf::RenderWindow& window);

		/*   Destructor  */
		~Tuple();
	};
}


