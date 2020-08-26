#include "MenuObjects.h"

/*
	Implementation file for menuobjects.h
*/


namespace MenuObjects {

	/*  Button Class  */

	//Button Default Constructor
	Button::Button() {
		clicked = false;
		hovered = false;
	}
	
	Button::Button(const sf::Vector2f & pos, const std::string & msg,
		const short fontCode, const int textSize,
		const sf::Vector2f & tightness)
	{
		clicked = false;
		hovered = false;

		//init Functions
		initText(msg, fontCode);
		setSize(textSize, tightness);
		initColors();
		setPosition(pos);
	}


	/*  Init Functions  */

	void Button::initText(const std::string& msg,
		const short font)
	{
		/*
			Initialize our button text with a font, textSize
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

	void Button::initColors(const sf::Color& prim,
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
	std::string Button::getString() const {
		return text.getString();
	}

	bool Button::isHovered(const sf::RenderWindow& window) const {
		sf::Vector2f pos = convert( sf::Mouse::getPosition(window) );
		return box.getGlobalBounds().contains(pos);
	}

	bool Button::isClicked() const {
		return clicked;
	}

	sf::Color Button::getPrimColor() const{
		return box.getFillColor();
	}

	sf::Color Button::getSecColor() const {
		return box.getOutlineColor();
	}

	sf::Color Button::getTxtColor() const {
		return text.getFillColor();
	}
	//end accessors


	/*  Modifiers  */
	void Button::setString(const std::string & newString)
	{
	}

	void Button::setSize(const int textSize, const sf::Vector2f&
		tightness)
	{
		/*
			Calculate default and standard sizes based on the
			window for the box and text.
			The button size can thereafter be scaled or reset
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
			(rectHeight - (adj / 2.f))/ 2.f);

		box.setSize(sf::Vector2f(rectLength, rectHeight));
		box.setOutlineThickness(thickness);
		box.setOrigin(rectOrigin);
	}

	void Button::setOutlineThickness(const int thickness) {
		box.setOutlineThickness(thickness);
	}

	void Button::setPosition(const sf::Vector2f & pos) {
		text.setPosition(pos);
		box.setPosition(pos);
	}

	void Button::setPrimColor(const sf::Color & newPrim) {
		primColor = newPrim;
		box.setFillColor(newPrim);
	}

	void Button::setSecColor(const sf::Color & newSec){
		box.setOutlineColor(newSec);
	}

	void Button::setTxtColor(const sf::Color & newTxtcolor) {
		text.setFillColor(newTxtcolor);
	}

	void Button::setAnimateColor(const sf::Color & newCol) {
		animateColor = newCol;
	}
	//END MODIFIERS



	/*  Other Private Functions  */

	//Button Functionality
	void Button::animateOnHover()
	{
		sf::Vector2f scaling = sf::Vector2f(1.1f, 1.1f);

		box.setFillColor(animateColor);
		box.scale(scaling);
		text.scale(scaling);
	}

	void Button::resetSize()
	{
		sf::Vector2f reset = sf::Vector2f(1, 1);
		text.setScale(reset);
		box.setScale(reset);
	}


	
	/*  Other Public Functions  */

	void Button::update(const sf::RenderWindow& window)
	{
		if (isHovered(window)) {

			if (!hovered)
				animateOnHover();
			hovered = true;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
				clicked = true;
		}
		else if (hovered) {

			//reset sieze
			cout << "reseting Size!" << endl;
			resetSize();

			//reset colors
			setPrimColor(primColor);
			hovered = false;
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







	/*  Textbox Class  */

//Textbox default Constructor
	Textbox::Textbox()
	{
	}

	/*  Accessors  */


	/*  Modifiers  */


	/*  Other Private Functions  */

	/*  Other Public Functions  */



	/*  Destructors  */
	Textbox::~Textbox()
	{
	}
	//END Textbox Class


}


	