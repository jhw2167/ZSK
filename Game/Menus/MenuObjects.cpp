#include "MenuObjects.h"

/*
	Implementation file for menuobjects.h
*/


//Base MenuObj Class
namespace MenuObjects {

	/*  Menu Object Base Class */
	const float MenuObject::adj = 10.f;

	//MenuObject Default Constructor
	MenuObject::MenuObject() {
		clickable = false;
		clicked = false;
		hovered = false;
		currState = STATE::MAIN_MENU;
	}

	MenuObject::MenuObject(const STATE currentState, const sf::Vector2f & pos,
		const std::string & msg, const zsk::FONT_CODE fontCode, const int textSize,
		const bool canBeClicked, const STATE newStateOnClick, const sf::Vector2f & tghtness)
	{
		//States
		currState = currentState;
		nextState = newStateOnClick;

		//core Fields
		clickable = canBeClicked;
		clicked = false;
		hovered = false;
		animateScale = sf::Vector2f(1.1f, 1.1f);
		boxSize = sf::Vector2f(20.f, 20.f);

		//init Functions
		initText(msg, fontCode);
		setSize(textSize, tghtness, true);
		initColors();
		setPosition(pos);
	}

	//For tuples
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
		initText("", zsk::ARIAL);
		initColors();
		animateScale = sf::Vector2f(1.f, 1.f);

		clickable = canBeClicked;
		clicked = false;
		hovered = false;
	}


	//Copy Constructor
	MenuObject::MenuObject(const MenuObject & rhs)
	{
		/*
			Copy constructor matches all base class
			variables between two objs
		*/
		animateColor = rhs.animateColor;
		animateColor2 = rhs.animateColor2;
		animateScale = rhs.animateScale;
		box = rhs.box;
		boxSize = rhs.boxSize;
		clickable = rhs.clickable;
		clicked = rhs.clicked;
		currState = rhs.currState;
		hovered = rhs.hovered;
		nextState = rhs.nextState;
		primColor = rhs.primColor;
		secColor = rhs.secColor;
		text = rhs.text;
		textDims = rhs.textDims;
		tightness = rhs.tightness;
		txtAlign = rhs.txtAlign;
	}

	//End Constructors 

	/*  Init Functions  */

	void MenuObject::initText(const std::string& msg,
		const zsk::FONT_CODE font)
	{
		/*
			Initialize our MenuObject text with a font, textSize
			and color
		*/

		switch (font)
		{
		case zsk::ARIAL:
			text.setFont(zsk::art::arial);
			break;

		case zsk::ARCDE:
			text.setFont(zsk::art::arcade);
			break;

		default:
			text.setFont(zsk::art::arial);
			break;
		}

		txtAlign = CNTR;
		text.setString(msg);
	}

	void MenuObject::initColors(const sf::Color& prim,
		const sf::Color& sec,
		const sf::Color& txt)
	{
		//box
		primColor = prim;
		box.setFillColor(prim);
		box.setOutlineColor(sec);
		secColor = sec;
		animateColor2 = sec;

		//text
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

	sf::Color MenuObject::getAnimateColor() const {
		return animateColor;
	}

	sf::Color MenuObject::getSecColor() const {
		return secColor;
	}

	sf::Color MenuObject::getAnimateColor2() const {
		return animateColor2;
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
		float rectLength = text.getLocalBounds().width * tightness.x;
		float rectHeight = text.getLocalBounds().height * tightness.y + adj;

		boxSize = sf::Vector2f(rectLength, rectHeight);
	

		sf::Vector2f rectOrigin = sf::Vector2f(boxSize.x / 2.f,
			(boxSize.y - (adj / 2.f)) / 2.f);

		box.setSize(boxSize);
		box.setOutlineThickness(thickness);
		box.setOrigin(rectOrigin);
	}

	void MenuObject::adjTextToBox(const sf::Vector2f& adjm) {
		text.setPosition(text.getPosition() + adjm);
	}

	void MenuObject::setOutlineThickness(const float thickness) {
		box.setOutlineThickness(thickness);
	}

	void MenuObject::setTextStyle(const sf::Text::Style & style) {
		text.setStyle(style);
	}

	void MenuObject::setTextSpacing(const float spc){
		text.setLetterSpacing(spc);
	}

	void MenuObject::setFont(const zsk::FONT_CODE font) {
		initText(text.getString(), font);
	}

	void MenuObject::alignText(const ALIGN aln)
	{
		sf::Vector2f textSize(text.getLocalBounds().width,
			text.getLocalBounds().height);

		sf::Vector2f pos(box.getPosition());
		sf::Vector2f origin(0.f, textSize.y / 2.f);
		

		switch (aln)
		{
		case LEFT:
			pos.x -= boxSize.x / 2.f;
			pos.x += adj;

			//no origin change
			break;

		case CNTR:
			origin.x += textSize.x / 2.f;
			//no position change
			break;

		case RGHT:
			pos.x += boxSize.x / 2.f;
			pos.x -= adj;

			origin.x += textSize.x;
			break;
		}

		//set values
		txtAlign = aln;
		text.setOrigin(origin);
		text.setPosition(pos);
	}

	void MenuObject::setPosition(const sf::Vector2f & pos) {
		text.setPosition(pos);
		box.setPosition(pos);
	}

	void MenuObject::setBoxOrigin(const sf::Vector2f & org) {
		box.setOrigin(org);
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
		secColor = newSec;
		box.setOutlineColor(newSec);
	}

	void MenuObject::setTxtColor(const sf::Color & newTxtcolor) {
		text.setFillColor(newTxtcolor);
	}

	void MenuObject::setAnimateColor(const sf::Color & newCol) {
		animateColor = newCol;
	}

	void MenuObject::setAnimateColor2(const sf::Color & newCol) {
		animateColor2 = newCol;
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
		const zsk::FONT_CODE fontCode, const int textSize, const bool canBeClicked,
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
		box.setOutlineColor(animateColor2);
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

	char Button::getType() const {
		return 'b';
	}

	STATE Button::update(sf::RenderWindow& window)
	{
		/*
			The main update function for each button should
			be run once per while loop refresh.  If the
			button is clickable it tests for hovering,
			animates the button, and sets click to
			true if necessary
		*/

		//clicked set false initially everytime
		clicked = false;

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
				setSecColor(secColor);
				hovered = false;

			}
		}

		if (clicked) {
			return nextState;
		}
		else {
			return currState;
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




//Textbox Class
namespace MenuObjects {

	/*  Textbox Class  */

//Textbox default Constructor
	Textbox::Textbox() : MenuObject() { events = nullptr; }

	Textbox::Textbox(STATE currentState, const sf::Vector2f & pos,
		const std::string & msg, const zsk::FONT_CODE fontCode,
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
		forceUpperLetters = false;

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
	{
		events = nullptr;
		maxMsgSize = 18;
		forceUpperLetters = false;
		animateScale = sf::Vector2f(1, 1);

		rmDefTextOpts = true;
		interval = 30;
		counter = 1;
	}

	//End Constructors

	void Textbox::setEventsPtr(const std::shared_ptr<std::vector<sf::Event>>& evs) {
		events = evs;
	}

	void Textbox::setString(const std::string & newString)
	{
		if (newString.length() <= maxMsgSize)
		{
			text.setString(newString);
			fitTextToBox(tightness, txtAlign);
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

	void Textbox::fitTextToBox(const sf::Vector2f & t, const ALIGN aln) {
		/*
			We want to center the text in the box vertically,
			and adjust the size of the text to fit properly
		*/

		//Set new tightness
		tightness = t;

		//calc new char size
		float yText = (boxSize.y - adj) / t.y;
		float xText = boxSize.x / t.x;
		unsigned int newTextSize = static_cast<unsigned int>(std::min(xText, yText));
		text.setCharacterSize(newTextSize);

		float textLength(text.getLocalBounds().width);
		float barrier = (2 * box.getOutlineThickness()) + adj;
		while (textLength - barrier > boxSize.x) {
			newTextSize--;
			text.setCharacterSize(newTextSize);
			textLength = text.getLocalBounds().width;
		}
		
		//set new text pos and origin		
		alignText(aln);
	}

	void Textbox::setMaxMsgSize(int newSize) {
		maxMsgSize = newSize;
	}

	void Textbox::forceUpperCase(bool force) {
		forceUpperLetters = force;
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
		box.setOutlineColor(animateColor2);
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
					
					/*  Divide into force upper letters section  */

					//Check for backspace entered
					if (n == 8 && input.size() > 0) {
						size_t pos = input.find_last_not_of("|");

						if (pos != input.npos)
							input.erase(input.begin() + pos);
					}
					else if (n < 32 || n == 127) {
						// do nothing, not valid characters
					}
					else
					{
						//Non-letter valid symbols
						if (forceUpperLetters) {
							c = toupper(c);
						}
						input += c;
					}
						
					animateCursor(input);
				}

				//exit text box condition
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
			if (counter == 0) {
				counter = -1;
			}
			else
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
			if (counter == 0) {
				counter = 1;
			}
			else
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

	char Textbox::getType() const {
		return 't';
		//textBox type designated as char 't'
	}

	STATE Textbox::update(sf::RenderWindow& window)
	{
		/*
			The main update function for each textBox should
			be run once per while loop refresh.  If the
			button is clickable it tests for hovering,
			animates the button, and sets click to
			true if necessary
		*/

		if (events == nullptr) {
			cout << "EVENTS PTR NOT ASSIGNED: Please call textbox.setEventsPtr()\n";
			clickable = false;
		}

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
				setSecColor(secColor);
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
		for (size_t i = 0; i != objs.size(); i++)
		{
			float per = percLengths.at(i);
			float totalLength = boxSize.x;

			sf::Vector2f objSize = sf::Vector2f(per * boxSize.x, boxSize.y);
			sf::Vector2f startPos = sf::Vector2f(box.getPosition().x -
				boxSize.x / 2.f, box.getPosition().y);

			sf::Vector2f pos = startPos;

			//determine position recursively
			for (auto& obj : internals) {
				pos.x += obj->getBoxSize().x;
			}

			pos.x += objSize.x / 2.f;

			//potential objects to add
			Button* newButton = new Button(currState, pos, objSize, !clickable, currState);
			Textbox* newTextbox = new Textbox(currState, pos, objSize, !clickable, currState);

			switch (objs.at(i)) {

			case 'b':
				//Add button to back of vector
				internals.push_back(newButton);
				delete newTextbox;
				break;

			case 't':
				//Add textBox to back of vector
				internals.push_back(newTextbox);
				delete newButton;
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
		objTypes = objs;
		addObjs(objs);
	}


	//Move Constructor
	Tuple::Tuple(Tuple&& rhs)
		: MenuObject(rhs)
	{
		/*
			copy all the pointers from one tuple to another
			so we dont lose track!!
		*/

		for (auto& ptr : rhs.internals) {
			internals.push_back(ptr);
			ptr = nullptr;
		}

		percLengths = rhs.percLengths;
		objTypes = rhs.objTypes;
	}


	//Copy Constructor - DELETED, use MOVE constructor 
	Tuple::Tuple(const Tuple& rhs)
		: MenuObject(rhs) 
	{
		/*
			Create deeo copy all the objects from one tuple to another
			so we dont lose information
		*/

		for (auto& ptr : rhs.internals) 
		{
			//create new button and tbox
			Button* b = new Button();
			Textbox* t = new Textbox();

			switch (ptr->getType())
			{
			case 'b':
				//init button with rhs values
				*b = Button(*dynamic_cast<Button*>(ptr));
				internals.push_back(b);
				delete t;
				break;

			case 't':
				*t = Textbox(*dynamic_cast<Textbox*>(ptr));
				internals.push_back(t);
				delete b;
				break;
			}
		}

		percLengths = rhs.percLengths;
		objTypes = rhs.objTypes;
	}

	//End constructors

	//Accessors
	std::vector<MenuObject*>* Tuple::getObjs() {
		return &internals;
	}

	char Tuple::getType() const {
		return 'u';
		//tuple type designated as char 'u'
	}


	/*  Virtual Functions  */
	STATE Tuple::update(sf::RenderWindow & window)
	{
		for (auto& menObj : internals) {
			STATE gs = menObj->update(window);
			if (gs != currState)
				return gs;
		}

		return currState;
	}

	void Tuple::updateCurrState(const STATE curr) {
		currState = curr;

		for (auto& ptr : internals) {
			ptr->updateCurrState(curr);
		}
	}

	void Tuple::updateNextState(const STATE next) {
		nextState = next;

		for (auto& ptr : internals) {
			ptr->updateNextState(next);
		}
	}

	void Tuple::draw(sf::RenderWindow & window)
	{
		for (auto& menObj : internals) {
			menObj->draw(window);
		}
	}


	Tuple::~Tuple()
	{
		/*
			delete all memory that we allocated
		*/
		for (auto& obj : internals)
		{
			delete obj;
			obj = nullptr;
		}

		internals.clear();
	}

	/*  Unique public methods  */
	// Public Methods
	void Tuple::setOutlineThickness(const float thickness)
	{
		/*
			Outline thickness increase the size of our tuple
			objects so it must be dealth with specially
		*/

		for (size_t i = 0; i != internals.size(); i++)
		{
			float per = percLengths.at(i);
			float totalLength = boxSize.x;
			float outline = 2 * thickness;

			sf::Vector2f objSize = sf::Vector2f((per * boxSize.x) - outline, boxSize.y);
			sf::Vector2f startPos = sf::Vector2f(box.getPosition().x -
				boxSize.x / 2.f, box.getPosition().y);

			//adj pos for outline and box origin at center
			sf::Vector2f pos = startPos;
			pos.x += thickness;
			pos.x += (objSize.x / 2.f);


			//determine position recursively
			for (size_t j = 0; j != i; j++) {
				pos.x += (internals.at(j)->getBoxSize().x + outline);
			}

			//set values
			internals.at(i)->setBoxSize(objSize);
			internals.at(i)->setPosition(pos);
			internals.at(i)->setOutlineThickness(thickness);
		}
	}

}