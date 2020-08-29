#include "MenuObjects.h"

/*
	Implementation file for menuobjects.h
*/


namespace MenuObjects {

	/*  Menu Object Base Class */


		//MenuObject Default Constructor
	MenuObject::MenuObject() {
		clickable = false;
		clicked = false;
		hovered = false;
	}

	MenuObject::MenuObject(const sf::Vector2f & pos, const std::string & msg,
		const short fontCode, const int textSize, const bool canBeClicked,
		const sf::Vector2f & tightness)
	{
		clickable = canBeClicked;
		clicked = false;
		hovered = false;
		animateScale = sf::Vector2f(1.1, 1.1);

		//init Functions
		initText(msg, fontCode);
		setSize(textSize, tightness);
		initColors();
		setPosition(pos);
	}


	/*  Init Functions  */

	void MenuObject::initText(const std::string& msg,
		const short font)
	{
		/*
			Initialize our MenuObject text with a font, textSize
			and color
		*/

		switch (font)
		{
		case ARIAL:
			text.setFont(zsk::art::arial);
			break;

		case ARCDE:
			text.setFont(zsk::art::arcade);
			break;

		default:

			text.setFont(zsk::art::arial);
			break;
		}

		text.setString(msg);
	}

	void MenuObject::initColors(const sf::Color& prim,
		const sf::Color& sec,
		const sf::Color& txt)
	{
		primColor = prim;
		box.setFillColor(prim);
		box.setOutlineColor(sec);
		text.setFillColor(txt);
	}
	//END INIT FUNCTIONS


	/*  Accessors  */
	std::string MenuObject::getString() const {
		return text.getString();
	}

	bool MenuObject::isHovered(sf::RenderWindow& window) const {
		sf::Vector2f pos = convert(sf::Mouse::getPosition(window));
		return box.getGlobalBounds().contains(pos);
	}

	bool MenuObject::isClicked() const {
		return clicked;
	}

	bool MenuObject::isClickable() const {
		return clickable;
	}

	sf::Color MenuObject::getPrimColor() const {
		return box.getFillColor();
	}

	sf::Color MenuObject::getSecColor() const {
		return box.getOutlineColor();
	}

	sf::Color MenuObject::getTxtColor() const {
		return text.getFillColor();
	}
	//end accessors


	/*  Modifiers  */
	void MenuObject::setString(const std::string & newString)
	{
	}

	void MenuObject::setSize(const int textSize, const sf::Vector2f&
		tightness)
	{
		/*
			Calculate default and standard sizes based on the
			window for the box and text.
			The MenuObject size can thereafter be scaled or reset
			entirely.
		*/

		float thickness = textSize / 5.f;

		text.setCharacterSize(textSize);

		//set origin in the middle of th text
		float length = text.getLocalBounds().width;
		float height = text.getLocalBounds().height;

		sf::Vector2f origin = sf::Vector2f(length / 2.f, height / 2.f);
		text.setOrigin(origin);

		//center the box around the text
		const float adj = 20.f;
		float rectLength = text.getLocalBounds().width * tightness.x;
		float rectHeight = text.getLocalBounds().height * tightness.y + adj;

		sf::Vector2f rectOrigin = sf::Vector2f(rectLength / 2.f,
			(rectHeight - (adj / 2.f)) / 2.f);

		box.setSize(sf::Vector2f(rectLength, rectHeight));
		box.setOutlineThickness(thickness);
		box.setOrigin(rectOrigin);
	}

	void MenuObject::setOutlineThickness(const int thickness) {
		box.setOutlineThickness(thickness);
	}

	void MenuObject::setPosition(const sf::Vector2f & pos) {
		text.setPosition(pos);
		box.setPosition(pos);
	}

	void MenuObject::setPrimColor(const sf::Color & newPrim) {
		primColor = newPrim;
		box.setFillColor(newPrim);
	}

	void MenuObject::setSecColor(const sf::Color & newSec) {
		box.setOutlineColor(newSec);
	}

	void MenuObject::setTxtColor(const sf::Color & newTxtcolor) {
		text.setFillColor(newTxtcolor);
	}

	void MenuObject::setAnimateColor(const sf::Color & newCol) {
		animateColor = newCol;
	}

	void MenuObject::setAnimateScaler(const sf::Vector2f & newScale) {
		animateScale = newScale;
	}

	void MenuObject::setClickable(const bool canBeClicked) {
		clickable = canBeClicked;
	}
	//END MODIFIERS



	/*  Other Private Functions  */

	//MenuObject Functionality - virtual functions

	void MenuObject::waitForUnclick() {
		while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {}
		clickable = true;
	}



	/*  Other Public Functions  */
	void MenuObject::update(sf::RenderWindow& window)
	{
		/*
			The main update function for each MenuObject should
			be run once per while loop refresh.  If the
			MenuObject is clickable it tests for hovering,
			animates the MenuObject, and sets click to
			true if necessary
		*/
		if (clickable)
		{
			if (isHovered(window)) {

				if (!hovered)
					animateOnHover();
				hovered = true;

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					clicked = true;
				}

			}
			else if (hovered) {

				//reset sieze
				resetSize();

				//reset colors
				setPrimColor(primColor);
				hovered = false;
			}
		}

	}

	void MenuObject::bufferClickable() {
		/*
			Waits for user to release mouse MenuObject so buttons are
			not clicked unintentionally.
		*/
		std::thread t1{ &MenuObject::waitForUnclick, this };
		t1.detach();
	}

	void MenuObject::draw(sf::RenderWindow & window) {
		window.draw(box);
		window.draw(text);
	}


	//End Base Menu Object Class
}

namespace MenuObjects {

	/*  Button Class  */

	//Button Default Constructor
	Button::Button() : MenuObject() {}

	Button::Button(const sf::Vector2f & pos, const std::string & msg,
		const short fontCode, const int textSize, const bool canBeClicked,
		const sf::Vector2f & tightness) :
		MenuObject(pos, msg, fontCode, textSize, canBeClicked, tightness) {}


	/*  Init Functions - Base Class */

	//END INIT FUNCTIONS


	/*  Accessors - Base Class */

	//end accessors


	/*  Modifiers - Base Class */

	//END MODIFIERS



	/*  Other Private Functions  */

	//Button Functionality - virtual functions
	void Button::animateOnHover()
	{
		box.setFillColor(animateColor);
		box.scale(animateScale);
		text.scale(animateScale);
	}

	void Button::resetSize()
	{
		sf::Vector2f reset = sf::Vector2f(1, 1);
		text.setScale(reset);
		box.setScale(reset);
	}




	/*  Other Public Functions  */

	void Button::update(sf::RenderWindow& window)
	{
		/*
			The main update function for each button should
			be run once per while loop refresh.  If the
			button is clickable it tests for hovering,
			animates the button, and sets click to
			true if necessary
		*/
		if (clickable)
		{
			if (isHovered(window)) {

				if (!hovered)
					animateOnHover();
				hovered = true;

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					clicked = true;
				}

			}
			else if (hovered) {

				//reset sieze
				resetSize();

				//reset colors
				setPrimColor(primColor);
				hovered = false;
			}
		}

	}

	void Button::draw(sf::RenderWindow & window) {
		window.draw(box);
		window.draw(text);
	}


	/*  Destructors  */
	Button::~Button()
	{
	}
	//END Button Class

}

namespace MenuObjects {

	/*  Textbox Class  */

//Textbox default Constructor
	Textbox::Textbox() : MenuObject() { events = nullptr; }

	Textbox::Textbox(const sf::Vector2f & pos, const std::string & msg,
		const short fontCode, const int textSize,
		const bool canBeClicked, const sf::Vector2f & tightness) :
		MenuObject(pos, msg, fontCode, textSize, canBeClicked, tightness) 
	{
		lockClick = false;
		events = nullptr;

		animateScale = sf::Vector2f(1, 1);
		MenuObject::setTxtColor(zsk::art::lightTertCol);

		rmDefTextOpts = true;
	}

	void Textbox::setEventsPtr(std::vector<sf::Event>* evs){
		events = evs;
	}
	
	/*  Init Functions - Base Class */

	//END INIT FUNCTIONS


	/*  Accessors - Base Class */

	//end accessors


	/*  Modifiers - Base Class */

	//END MODIFIERS



	/*  Other Private Functions  */

	//Button Functionality - virtual functions
	void Textbox::animateOnHover()
	{
		box.setFillColor(animateColor);
		box.scale(animateScale);
		text.scale(animateScale);
	}

	void Textbox::resetSize()
	{
		sf::Vector2f reset = sf::Vector2f(1, 1);
		text.setScale(reset);
		box.setScale(reset);
	}

	void Textbox::checkTextInput(sf::RenderWindow& window)
	{
		/*
			checks for text input in threaded while loop
		*/

		//gets text from keyboard
	
		if (!events->empty())
		{
			std::string input = text.getString();
			
			for (size_t i = events->size() - 1; i != -1; i--)
			{
				sf::Event e = events->at(i);
				if (e.type == sf::Event::TextEntered) 
				{
					char c = e.text.unicode;
					int n = c;
					
					if (n == 8)
						input.pop_back();
					else if (n < 32 || n == 127) {
						// do nothing, not valid characters
					}
					else
						input += e.text.unicode;
					
					text.setString(input);
				}

				//escape condition
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					clicked = false;
			}

		}

		lockClick = false;
		//function exits, can be engaged again upon reclick
	}

	void Textbox::removeDefText()
	{
		setTxtColor(zsk::art::secColor);
		text.setString("");
		rmDefTextOpts = false;
	}




	/*  Other Public Functions  */

	void Textbox::update(sf::RenderWindow& window)
	{
		/*
			The main update function for each textBox should
			be run once per while loop refresh.  If the
			button is clickable it tests for hovering,
			animates the button, and sets click to
			true if necessary
		*/

		if (clickable)
		{
			if (isHovered(window)) {

				if (!hovered)
					animateOnHover();
				hovered = true;
				//little trick to set the animation only once

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					clicked = true;

					if (rmDefTextOpts)
						removeDefText();
				}

			}
			else if (hovered) {

				//reset sieze
				resetSize();

				//reset colors
				setPrimColor(primColor);
				hovered = false;
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				
				clicked = false;
			}


			//if clicked, check events for text input
			if (clicked)
				checkTextInput(window);
		}

	}


	void Textbox::draw(sf::RenderWindow & window) {
		window.draw(box);
		window.draw(text);
	}



	/*  Destructors  */
	Textbox::~Textbox()
	{}
	//END Textbox Class


}


	