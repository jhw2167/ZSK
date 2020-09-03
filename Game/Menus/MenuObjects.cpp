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

	MenuObject::MenuObject(const STATE currentState, const sf::Vector2f & pos,
		const std::string & msg, const short fontCode, const int textSize,
		const bool canBeClicked, const STATE newStateOnClick, const sf::Vector2f & tghtness)
	{
		//States
		currState = currentState;
		nextState = newStateOnClick;

		//core Fields
		clickable = canBeClicked;
		clicked = false;
		hovered = false;
		animateScale = sf::Vector2f(1.1, 1.1);
		boxSize = sf::Vector2f(20.f, 20.f);

		//init Functions
		initText(msg, fontCode);
		setSize(textSize, tghtness, true);
		initColors();
		setPosition(pos);
	}

	MenuObject::MenuObject(const STATE currentState,
		const sf::Vector2f & pos,
		const sf::Vector2f & size, 
		const bool canBeClicked, 
		const STATE newStateOnClick)
	{
		currState = currentState;
		nextState = newStateOnClick;

		setBoxSize(size);
		setPosition(pos);

		clickable = canBeClicked;
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

	int MenuObject::getTextSize() const {
		return text.getCharacterSize();
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

	sf::Vector2f MenuObject::getPosition() const {
		return box.getPosition();
	}

	sf::Vector2f MenuObject::getBoxSize() const {
		return boxSize;
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

	float MenuObject::getOutlineThickness() const {
		return box.getOutlineThickness();
	}
	//end accessors


	/*  Modifiers  */
	void MenuObject::setString(const std::string & newString)
	{
		text.setString(newString);
		setSize(text.getCharacterSize(), tightness);
	}

	void MenuObject::setSize(const int textSize, const sf::Vector2f&
		tghtness, const bool init)
	{
		/*
			Calculate default and standard sizes based on the
			window for the box and text.
			The MenuObject size can thereafter be scaled or reset
			entirely.

			Certain values are set only on initialization
		*/

		float thickness = textSize / 5.f;
		tightness = tghtness;

		text.setCharacterSize(textSize);
		
		float height = text.getLocalBounds().height;
		float length = text.getLocalBounds().width;

		textDims = sf::Vector2f(length, height);

		//set origin in the middle of th text
		sf::Vector2f origin = sf::Vector2f(length / 2.f, textDims.y / 2.f);
		text.setOrigin(origin);

		//center the box around the text
		const float adj = 10.f;
		float rectLength = text.getLocalBounds().width * tightness.x;
		float rectHeight = text.getLocalBounds().height * tightness.y + adj;

		boxSize = sf::Vector2f(rectLength, rectHeight);
	

		sf::Vector2f rectOrigin = sf::Vector2f(boxSize.x / 2.f,
			(boxSize.y - (adj / 2.f)) / 2.f);

		box.setSize(boxSize);
		box.setOutlineThickness(thickness);
		box.setOrigin(rectOrigin);
	}

	void MenuObject::adjTextToBox(const sf::Vector2f& adj) {
		text.setPosition(text.getPosition() + adj);
	}

	void MenuObject::setOutlineThickness(const int thickness) {
		box.setOutlineThickness(thickness);
	}

	void MenuObject::setTextStyle(const sf::Text::Style & style) {
		text.setStyle(style);
	}

	void MenuObject::setTextSpacing(const float spc){
		text.setLetterSpacing(spc);
	}

	void MenuObject::setPosition(const sf::Vector2f & pos) {
		text.setPosition(pos);
		box.setPosition(pos);
	}

	void MenuObject::setBoxSize(const sf::Vector2f & size) {
		boxSize = size;
		sf::Vector2f rectOrigin = sf::Vector2f(boxSize.x / 2.f,
			(boxSize.y) / 2.f);

		box.setSize(boxSize);
		box.setOrigin(rectOrigin);
	}

	void MenuObject::updateCurrState(const STATE curr) {
		currState = curr;
	}

	void MenuObject::updateNextState(const STATE next) {
		nextState = next;
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
	
	void MenuObject::bufferClickable() {
		/*
			Waits for user to release mouse MenuObject so buttons are
			not clicked unintentionally.
		*/
		std::thread t1{ &MenuObject::waitForUnclick, this };
		t1.detach();
	}

	//End Base Menu Object Class
}




//Button Class
namespace MenuObjects {

	/*  Button Class  */

	//Button Default Constructor
	Button::Button() : MenuObject() {}

	Button::Button(STATE currentState, const sf::Vector2f & pos, const std::string & msg,
		const short fontCode, const int textSize, const bool canBeClicked,
		STATE newStateOnClick, const sf::Vector2f & tightness) :
		MenuObject(currentState, pos, msg, fontCode, textSize,
			canBeClicked, newStateOnClick, tightness) {}

	Button::Button(const STATE currentState, const sf::Vector2f & pos,
		const sf::Vector2f & boxSize, const bool canBeClicked,
		const STATE newStateOnClick) 
		: MenuObject(currentState, pos, boxSize, canBeClicked, newStateOnClick)
	{
	}


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

	STATE Button::update(sf::RenderWindow& window)
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

		if (clicked) 
			return nextState;
		else 
			return currState;
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




//Textbox Class
namespace MenuObjects {

	/*  Textbox Class  */

//Textbox default Constructor
	Textbox::Textbox() : MenuObject() { events = nullptr; }

	Textbox::Textbox(STATE currentState, const sf::Vector2f & pos,
		const std::string & msg, const short fontCode,
		const int textSize, const bool canBeClicked,
		STATE newStateOnClick, const sf::Vector2f & tghtness) :
		MenuObject(currentState, pos, msg, fontCode, textSize, canBeClicked,
			newStateOnClick, tghtness)
	{
		//init Textsize
		setSize(textSize, tghtness, true);

		//Basic Textbox facilities
		events = nullptr;
		maxMsgSize = 18;

		//Animation facilities
		animateScale = sf::Vector2f(1, 1);
		MenuObject::setTxtColor(zsk::art::lightTertCol);

		rmDefTextOpts = true;
		interval = 30;
		counter = 1;

	}

	//For tuples
	Textbox::Textbox(const STATE currentState, const sf::Vector2f & pos,
		const sf::Vector2f & boxSize, const bool canBeClicked,
		const STATE newStateOnClick)
		: MenuObject(currentState, pos, boxSize, canBeClicked, newStateOnClick)
	{}

	//End Constructors


	void Textbox::setEventsPtr(std::vector<sf::Event>* evs){
		events = evs;
	}

	void Textbox::setString(const std::string & newString)
	{
		if (newString.length() <= maxMsgSize)
		{
			text.setString(newString);
			setSize(text.getCharacterSize(), tightness, false);
		}
	}

	void Textbox::setSize(const int textSize, const sf::Vector2f&
		tghtness, const bool init)
	{
		/*
			Calculate default and standard sizes based on the
			window for the box and text.
			The MenuObject size can thereafter be scaled or reset
			entirely.

			Certain values are set only on initialization
		*/

		float thickness = textSize / 5.f;
		tightness = tghtness;

		text.setCharacterSize(textSize);

		float height = text.getLocalBounds().height;
		float length = text.getLocalBounds().width;

		if (init)
			textDims = sf::Vector2f(length, height);

		//set origin in the middle of th text
		sf::Vector2f origin = sf::Vector2f(length / 2.f, textDims.y / 2.f);
		text.setOrigin(origin);

		//center the box around the text
		const float adj = 10.f;
		float rectLength = text.getLocalBounds().width * tightness.x;
		float rectHeight = boxSize.y;

		if (init)
			rectHeight = text.getLocalBounds().height * tightness.y + adj;

		//Control for undersized words		
		rectLength = std::max(boxSize.x, rectLength);
		rectHeight = std::max(boxSize.y, rectHeight);

		if (init)
			boxSize = sf::Vector2f(rectLength, rectHeight);

		sf::Vector2f newSize = sf::Vector2f(rectLength, rectHeight);

		sf::Vector2f rectOrigin = sf::Vector2f(newSize.x / 2.f,
			(newSize.y - (adj / 2.f)) / 2.f);

		box.setSize(newSize);
		box.setOutlineThickness(thickness);
		box.setOrigin(rectOrigin);
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
		/*
			Set color, button pop and cursor to animate while
			textbox is selected
		*/

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
					
					if (n == 8 && input.size() > 0) {
						size_t pos = input.find_last_not_of("|");

						if (pos != input.npos)
							input.erase(input.begin() + pos);
					}
						
					else if (n < 32 || n == 127) {
						// do nothing, not valid characters
					}
					else
						input += e.text.unicode;
					
					animateCursor(input);
				}

				//escape condition
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					clicked = false;
			}

		}
		else {
			animateCursor(text.getString());
		}

		
	}

	void Textbox::animateCursor(std::string msg)
	{
		std::string c = "|";
		size_t cursorPos = msg.find_last_of(c);

		//check for switch to no cursor
		bool isCursor = (counter > 0) && (counter < interval);

		if (isCursor)
		{
			//ensure cursor not deleted
			if (cursorPos == msg.size() - 1) {
				//do nothing, cursor in corect spot
			}
			else if (cursorPos != msg.npos)
			{
				//ensure cursor is at the back
				msg.erase(msg.begin() + cursorPos);
				msg += c;
			}
			else
				msg += c;

			//increment counter
			counter += (counter / counter);

			if (counter >= interval)
				counter = -1;
		}
		else
		{
			if (msg.size() > 0)
			{
				if (cursorPos == msg.size() - 1) {
					msg.erase(msg.begin() + cursorPos);
				}
			}
			
			//increment counter
			counter -= (counter / counter);

			if (counter <= -interval)
				counter = 1;
		}
			
		setString(msg);
	}

	void Textbox::removeDefText()
	{
		setTxtColor(zsk::art::secColor);
		text.setString("");
		rmDefTextOpts = false;
	}




	/*  Other Public Functions  */

	STATE Textbox::update(sf::RenderWindow& window)
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

					if (rmDefTextOpts) {
						removeDefText();
						animateCursor(text.getString());
					}
						
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
			if (clicked) {
				checkTextInput(window);
			}
				
		}

		return currState;
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



//Tuple Class - for combination of textboxes and buttons
namespace MenuObjects {


		/*  Unique Private Methods  */
	void Tuple::addObjs(const std::vector<char>& objs)
	{
		for (size_t i = objs.size() - 1; i != -1; i--)
		{
			float per = percLengths.at(i);
			float totalLength = boxSize.x;

			sf::Vector2f objSize = sf::Vector2f(per * boxSize.x, boxSize.y);
			sf::Vector2f endPos = sf::Vector2f(box.getPosition().x +
				boxSize.x / 2.f, box.getPosition().y);

			sf::Vector2f pos = endPos;

			//determine position recursively
			for (auto& obj : internals) {
				pos.x -= obj->getBoxSize().x;
			}

			pos.x -= objSize.x / 2.f;

			//potential objects to add
			Button* newButton = new Button(currState, pos, objSize, !clickable, currState);
			 Textbox* newTextbox = new Textbox(currState, pos, objSize, !clickable, currState);

			switch (objs.at(i)) {

			case 'b':
				//Add button to back of vector
				internals.push_back(newButton);
				break;

			case 't':
				//Add textBox to back of vector
				internals.push_back(newTextbox);
				break;
			}
		}
	}



		/*  Constructors  */

	Tuple::Tuple(const STATE currentState, const sf::Vector2f & pos,
		const std::vector<char>& objs, 
		std::vector<float>& percentLengths,
		const sf::Vector2f & boxSize, const bool canBeClicked, 
		const STATE newStateOnClick) :
		MenuObject(currentState, pos, boxSize, canBeClicked, newStateOnClick)
	{
		percLengths = percentLengths;
		addObjs(objs);
	}

	std::vector<MenuObject*>& Tuple::getObjs() {
		return internals;
	}

	Tuple::~Tuple()
	{
		/*
			delete all memory that we allocated
		*/
		for (auto obj : internals)
		{
			delete obj;
			obj = nullptr;
		}

		internals.clear();
	}

	/*  Unique public methods  */
}